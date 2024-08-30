#include "mainwindow.h"

#include <QSystemTrayIcon>

#include "ui_mainwindow.h"
#include "QtAwesome.h"

#include "expenses/expensesoverviewwidget.h"
#include "recurring_expenses/recurringexpensesoverview.h"
#include "shared/datecontroller.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setupMenu()
    {
        ui->expensesButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_balance_scale));
        ui->chartsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_area_chart));
        ui->recurringButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_calendar_days));

        connect(ui->expensesButton, &QPushButton::pressed, this, &LSMainWindow::onExpenseMenuClicked);
        connect(ui->chartsButton, &QPushButton::pressed, this, &LSMainWindow::onChartsMenuClicked);
        connect(ui->recurringButton, &QPushButton::pressed, this, &LSMainWindow::onRecurringMenuClicked);

        m_expensesIndex = ui->widgetStack->addWidget(m_expensesOverviewWidget);
        m_chartsIndex = ui->widgetStack->addWidget(m_chartsWidget);
        m_recurringExpensesWidgetIndex = ui->widgetStack->addWidget(m_recurringExpensesWidget);
    }

    LSMainWindow::LSMainWindow(expenses::LSExpenseModel* expenseModel, expenses::LSRecurringExpenseModel* recurringModel, shared::LSDateController* dateController, expenses::LSRelatedExpenseProxyModel* relatedExpenseProxyModel, fa::QtAwesome* qtAwesome) :
        QMainWindow(nullptr),
        ui(new Ui::LSMainWindow),
        m_qtAwesome(qtAwesome),
        m_expenseModel(expenseModel),
        m_recurringModel(recurringModel),
        m_dateController(dateController)
    {
        setWindowTitle("Juno Expense Tracker");

        ui->setupUi(this);

        m_expensesOverviewWidget = new expenses::LSExpensesOverviewWidget(ui->widgetStack, statusBar(), expenseModel, qtAwesome);
        m_chartsWidget = new QWidget(this);
        m_recurringExpensesWidget = new expenses::LSRecurringExpensesOverview(this, relatedExpenseProxyModel, m_recurringModel);

        setupMenu();
        setupToolbox();

        createActions(); // TODO: Reuse for menu bar
        createTrayIcon();

        //ui->mdiArea->addSubWindow(expensesOverviewWidget);
    }

    void LSMainWindow::createActions()
    {
        minimizeAction = new QAction(tr("Mi&nimize"), this);
        connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

        maximizeAction = new QAction(tr("Ma&ximize"), this);
        connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

        restoreAction = new QAction(tr("&Restore"), this);
        connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

        quitAction = new QAction(tr("&Quit"), this);
        connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    }

    void LSMainWindow::createTrayIcon()
    {
        trayIconMenu = new QMenu(this);
        trayIconMenu->addAction(minimizeAction);
        trayIconMenu->addAction(maximizeAction);
        trayIconMenu->addAction(restoreAction);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(quitAction);

        trayIcon = new QSystemTrayIcon(this);
        trayIcon->setContextMenu(trayIconMenu);

        QIcon icon = m_qtAwesome->icon(fa::fa_solid, fa::fa_chart_simple);
        trayIcon->setIcon(icon);
        trayIcon->show();

        setWindowIcon(icon);

        //trayIcon->setToolTip(iconComboBox->itemText(index));
    }

    LSMainWindow::~LSMainWindow()
    {
        delete ui;
    }

    void LSMainWindow::setupToolbox()
    {
        ui->fromDate->setDisplayFormat("yyyy-MM-dd"); // TODO: Store date format in settings
        ui->toDate->setDisplayFormat("yyyy-MM-dd");

        ui->fromDate->setCalendarPopup(true);
        ui->toDate->setCalendarPopup(true);

        connect(ui->fromDate, &QDateEdit::dateChanged, [&]()
        {
            m_dateController->setFromDate(ui->fromDate->date());
        });
        connect(ui->toDate, &QDateEdit::dateChanged, this, [&]()
        {
            m_dateController->setToDate(ui->toDate->date());
        });
        connect(ui->searchButton, &QPushButton::clicked, this, [&]()
        {
            m_dateController->updateDateLimits();
        });

        // Filer dates set to current year for convenience
        int const currentYear = QDate::currentDate().year();
        ui->fromDate->setDate(QDate(currentYear, 1, 1));
        ui->toDate->setDate(QDate(currentYear, 12, 31));

        m_dateController->updateDateLimits();
    }

    void LSMainWindow::onExpenseMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_expensesIndex);
    }

    void LSMainWindow::onChartsMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_chartsIndex);
    }

    void LSMainWindow::onRecurringMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_recurringExpensesWidgetIndex);
    }
}

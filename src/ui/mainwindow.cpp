#include "mainwindow.h"

#include <QSystemTrayIcon>

#include "ui_mainwindow.h"
#include "QtAwesome.h"

#include "expenses/expensesoverviewwidget.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setupMenu()
    {
        ui->expensesButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_balance_scale));
        ui->chartsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_area_chart));

        connect(ui->expensesButton, &QPushButton::pressed, this, &LSMainWindow::onExpenseMenuClicked);
        connect(ui->chartsButton, &QPushButton::pressed, this, &LSMainWindow::onChartsMenuClicked);

        m_expensesIndex = ui->widgetStack->addWidget(expensesOverviewWidget);
        m_chartsIndex = ui->widgetStack->addWidget(chartsWidget);
    }

    LSMainWindow::LSMainWindow(expenses::LSExpenseModel* expenseModel, fa::QtAwesome* qtAwesome) :
        QMainWindow(nullptr),
        m_qtAwesome(qtAwesome),
        ui(new Ui::LSMainWindow),
        m_expenseModel(expenseModel)
    {
        setWindowTitle("Juno Expense Tracker");

        ui->setupUi(this);

        expensesOverviewWidget = new expenses::LSExpensesOverviewWidget(ui->widgetStack, statusBar(), expenseModel, qtAwesome);
        chartsWidget = new QWidget(this);

        setupMenu();

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

    void LSMainWindow::onExpenseMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_expensesIndex);
    }

    void LSMainWindow::onChartsMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_chartsIndex);
    }


}

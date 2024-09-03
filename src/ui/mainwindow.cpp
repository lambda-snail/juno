#include "mainwindow.h"

#include <QSystemTrayIcon>

#include "ui_mainwindow.h"
#include "QtAwesome.h"
#include "categories/categorymodel.h"

#include "expenses/expensesoverviewwidget.h"
#include "expense_charts/aggregateexpensemodel.h"
#include "expense_charts/expensechartswidget.h"
#include "recurring_expenses/recurringexpensesoverview.h"
#include "settings/settingswidget.h"
#include "shared/datecontroller.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setupMenu()
    {
        ui->expensesButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_balance_scale));
        ui->chartsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_area_chart));
        ui->recurringButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_calendar_days));
        ui->settingsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_gear));

        connect(ui->expensesButton, &QPushButton::pressed, this, &LSMainWindow::onExpenseMenuClicked);
        connect(ui->chartsButton, &QPushButton::pressed, this, &LSMainWindow::onChartsMenuClicked);
        connect(ui->recurringButton, &QPushButton::pressed, this, &LSMainWindow::onRecurringMenuClicked);
        connect(ui->settingsButton, &QPushButton::pressed, this, &LSMainWindow::onSettingsMenuClicked);

        m_expensesIndex = ui->widgetStack->addWidget(m_expensesOverviewWidget);
        m_chartsIndex = ui->widgetStack->addWidget(m_chartsWidget);
        m_recurringExpensesWidgetIndex = ui->widgetStack->addWidget(m_recurringExpensesWidget);
        m_settingsWidgetIndex = ui->widgetStack->addWidget(m_settingsWidget);
    }

    LSMainWindow::LSMainWindow(expenses::LSExpenseModel *expenseModel, QAbstractProxyModel *recurringModel,
                               QAbstractProxyModel *categoryModel, shared::LSDateController *dateController,
                               expenses::LSRelatedExpenseProxyModel *relatedExpenseProxyModel,
                               settings::LSSettingsModel* settingsModel,
                               fa::QtAwesome *qtAwesome) : QMainWindow(nullptr),
                                                           ui(new Ui::LSMainWindow),
                                                           m_qtAwesome(qtAwesome),
                                                           m_expenseModel(expenseModel),
                                                           m_recurringExpensesProxyModel(recurringModel),
                                                           m_dateController(dateController),
                                                           m_categoryModel(categoryModel)
    {
        ui->setupUi(this);

        setWindowTitle("Juno");

        m_expensesOverviewWidget = new expenses::LSExpensesOverviewWidget(ui->widgetStack, statusBar(), expenseModel, m_categoryModel, qtAwesome);
        m_recurringExpensesWidget = new expenses::LSRecurringExpensesOverview(ui->widgetStack, relatedExpenseProxyModel, m_recurringExpensesProxyModel, m_dateController, qtAwesome);

        auto aggregateExpenseModel = new expenses::LSAggregateExpenseModel(m_categoryModel);
        aggregateExpenseModel->setSourceModel(m_expenseModel);

        m_chartsWidget = new charts::LSExpenseChartsWidget(aggregateExpenseModel, ui->widgetStack);

        m_settingsWidget = new settings::LSSettingsWidget(settingsModel, ui->widgetStack);

        setupMenu();
        setupDateTool();
        setupCategoryTool();

        createActions();
        createMenuBar();
        createTrayIcon();
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

    void LSMainWindow::createMenuBar()
    {
        m_fileMenu = menuBar()->addMenu(tr("&File"));
        m_fileMenu->addAction(quitAction);

        m_helpMenu = menuBar()->addMenu(tr("&Help"));
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

    void LSMainWindow::setupDateTool()
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

    void LSMainWindow::setupCategoryTool()
    {
        ui->categoryView->setModel(m_categoryModel);
        ui->categoryView->setModelColumn(static_cast<int32_t>(categories::LSCategoryModel::Columns::category));

        ui->newCategoryButton->setText(tr(""));
        ui->deleteCategoryButton->setText(tr(""));

        ui->newCategoryButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_square_plus));
        ui->deleteCategoryButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_trash_can));

        ui->deleteCategoryButton->setDisabled(true);

        connect(ui->newCategoryButton, &QPushButton::clicked, this, [model = m_categoryModel]()
        {
            model->insertRow(0);
        });

        connect(ui->deleteCategoryButton, &QPushButton::clicked, this, [model = m_categoryModel, view = ui->categoryView, button = ui->deleteCategoryButton]()
        {
            QModelIndex const viewIndex = view->currentIndex();
            QModelIndex const index = model->mapToSource(viewIndex);
            model->removeRow(index.row());
            model->submit();
            model->revert();
            //model->sort()

            view->clearSelection();
            button->setEnabled(false);
        });

        connect(ui->categoryView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            [view = ui->categoryView, button = ui->deleteCategoryButton](const QItemSelection &selected, const QItemSelection &deselected)
        {
                if(selected.size() > 0)
                {
                    button->setEnabled(true);
                }
        });
    }

    void LSMainWindow::onExpenseMenuClicked() const
    {
        ui->widgetStack->setCurrentIndex(m_expensesIndex);
    }

    void LSMainWindow::onChartsMenuClicked() const
    {
        ui->widgetStack->setCurrentIndex(m_chartsIndex);
    }

    void LSMainWindow::onRecurringMenuClicked() const
    {
        ui->widgetStack->setCurrentIndex(m_recurringExpensesWidgetIndex);
    }

    void LSMainWindow::onSettingsMenuClicked() const
    {
        ui->widgetStack->setCurrentIndex(m_settingsWidgetIndex);
    }
}

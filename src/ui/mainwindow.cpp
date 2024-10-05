#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdialog.h>
#include <QSystemTrayIcon>

#include "QtAwesome.h"
#include "budget/budgetoverviewwidget.h"
#include "categories/categorymodel.h"

#include "expenses/expensesoverviewwidget.h"
#include "expense_charts/expensechartswidget.h"
#include "help/aboutwidget.h"
#include "recurring_expenses/recurringexpensesoverview.h"
#include "settings/settingswidget.h"
#include "shared/applicationcontext.h"
#include "shared/datecontroller.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setupMenu()
    {
        m_expensesOverviewWidget->setParent(ui->widgetStack);
        m_recurringExpensesWidget->setParent(ui->widgetStack);
        m_budgetWidget->setParent(ui->widgetStack);
        m_chartsWidget->setParent(ui->widgetStack);

        ui->expensesButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_balance_scale));
        ui->chartsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_area_chart));
        ui->recurringButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_calendar_days));
        ui->settingsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_gear));

        connect(ui->expensesButton, &QPushButton::pressed, this, &LSMainWindow::onExpenseMenuClicked);
        connect(ui->chartsButton, &QPushButton::pressed, this, &LSMainWindow::onChartsMenuClicked);
        connect(ui->recurringButton, &QPushButton::pressed, this, &LSMainWindow::onRecurringMenuClicked);
        connect(ui->settingsButton, &QPushButton::pressed, this, &LSMainWindow::onSettingsMenuClicked);
        connect(ui->monthlyBudgetButton, &QPushButton::pressed, this, &LSMainWindow::onMonthlyBudgetMenuClicked);

        m_expensesIndex = ui->widgetStack->addWidget(m_expensesOverviewWidget);
        m_chartsIndex = ui->widgetStack->addWidget(m_chartsWidget);
        m_budgetIndex = ui->widgetStack->addWidget(m_budgetWidget);
        m_recurringExpensesWidgetIndex = ui->widgetStack->addWidget(m_recurringExpensesWidget);
        m_settingsWidgetIndex = ui->widgetStack->addWidget(m_settingsWidget);
    }

    LSMainWindow::LSMainWindow(
                               QAbstractProxyModel* categoryModel,
                               shared::LSDateController *dateController,
                               QSettings* settings,
                               expenses::LSExpensesOverviewWidget* expensesOverviewWidget,
                               expenses::LSRecurringExpensesOverview* recurringExpensesOverviewWidget,
                               charts::LSExpenseChartsWidget* expenseChartWidget,
                               budget::LSBudgetOverviewWidget* budgetWidget,
                               settings::LSSettingsWidget *settingsWidget,
                               fa::QtAwesome *qtAwesome) : QMainWindow(nullptr),
                                                           ui(new Ui::LSMainWindow),
                                                           m_qtAwesome(qtAwesome),
                                                           m_expensesOverviewWidget(expensesOverviewWidget),
                                                           m_recurringExpensesWidget(recurringExpensesOverviewWidget),
                                                           m_settingsWidget(settingsWidget),
                                                           m_chartsWidget(expenseChartWidget),
                                                           m_budgetWidget(budgetWidget),
                                                           m_dateController(dateController),
                                                           m_categoryModel(categoryModel),
                                                           m_settings(settings)
    {
        ui->setupUi(this);

        setWindowTitle("Juno");

        m_aboutDialog = new LSAboutWidget(this);

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
        connect(quitAction, &QAction::triggered, this, &QCoreApplication::quit);

        // Help
        aboutAction = new QAction("&Help", this);
        connect(aboutAction, &QAction::triggered, m_aboutDialog, &QDialog::exec);
    }

    void LSMainWindow::createMenuBar()
    {
        m_fileMenu = menuBar()->addMenu(tr("&File"));
        m_fileMenu->addAction(quitAction);

        m_helpMenu = menuBar()->addMenu(tr("&Help"));
        m_helpMenu->addAction(aboutAction);
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
    }

    void LSMainWindow::setupDateTool()
    {
        QString format = m_settings->value(application::ApplicationContext::LocaleDateFormatKey).toString();
        ui->fromDate->setDisplayFormat(format);
        ui->toDate->setDisplayFormat(format);

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

        // Filter dates set to current year for convenience
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

        connect(ui->newCategoryButton, &QPushButton::clicked, [model = m_categoryModel, view = ui->categoryView]()
        {
            if(model->insertRow(0))
            {
                auto categoryIndex = model->index(0, static_cast<int>(categories::LSCategoryModel::Columns::category));
                model->setData(categoryIndex, QVariant("New Category"));

                auto limitIndex = model->index(0, static_cast<int>(categories::LSCategoryModel::Columns::spending_limit));
                model->setData(limitIndex, QVariant(0));

                model->submit();
                view->selectionModel()->setCurrentIndex(categoryIndex, QItemSelectionModel::ClearAndSelect);
            }
        });

        connect(ui->deleteCategoryButton, &QPushButton::clicked, [model = m_categoryModel, view = ui->categoryView, button = ui->deleteCategoryButton]()
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

        connect(ui->categoryView->selectionModel(), &QItemSelectionModel::selectionChanged,
            [view = ui->categoryView, button = ui->deleteCategoryButton](const QItemSelection &selected, const QItemSelection &deselected)
        {
                if(not selected.empty())
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

    void LSMainWindow::onMonthlyBudgetMenuClicked() const
    {
        ui->widgetStack->setCurrentIndex(m_budgetIndex);
    }
}

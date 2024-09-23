#pragma once

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "budget/budgetoverviewwidget.h"
#include "expense_charts/expensechartswidget.h"
#include "recurring_expenses/recurringexpensesoverview.h"
#include "settings/settingsmodel.h"
#include "settings/settingswidget.h"

namespace fa
{
    class QtAwesome;
}

namespace LambdaSnail::Juno
{
    namespace shared
    {
        class LSDateController;
    }

    namespace expenses
    {
        class LSExpensesOverviewWidget;
        class LSRecurringExpenseModel;
    }

    class LSMainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit LSMainWindow(
                     QAbstractProxyModel* categoryModel,
                     shared::LSDateController* dateController,
                     QSettings* settings,
                     expenses::LSExpensesOverviewWidget* expensesOverviewWidget,
                     expenses::LSRecurringExpensesOverview* recurringExpensesOverviewWidget,
                     charts::LSExpenseChartsWidget* expenseChartWidget,
                     LambdaSnail::Juno::budget::LSBudgetOverviewWidget* budgetWidget,
                     settings::LSSettingsWidget* settingsWidget,
                     fa::QtAwesome *qtAwesome);

        ~LSMainWindow() override = default;

    private:
        std::unique_ptr<Ui::LSMainWindow> ui;
        fa::QtAwesome * m_qtAwesome;

        int m_expensesIndex{};
        expenses::LSExpensesOverviewWidget* m_expensesOverviewWidget;

        int m_recurringExpensesWidgetIndex{};
        expenses::LSRecurringExpensesOverview* m_recurringExpensesWidget;

        int m_settingsWidgetIndex{};
        settings::LSSettingsWidget* m_settingsWidget;

        int m_chartsIndex{};
        QWidget* m_chartsWidget;

        int m_budgetIndex{};
        budget::LSBudgetOverviewWidget* m_budgetWidget;

        shared::LSDateController * m_dateController;
        QAbstractProxyModel * m_categoryModel;
        QSettings* m_settings;

        // System tray icon and menu
        QSystemTrayIcon*    trayIcon{};
        QAction*            minimizeAction{};
        QAction*            maximizeAction{};
        QAction*            restoreAction{};
        QAction*            quitAction{};
        QAction*            aboutAction;

        QMenu*              trayIconMenu{};
        QMenu*              m_helpMenu{};
        QMenu*              m_fileMenu{};

        QDialog*            m_aboutDialog;

        void setupDateTool();

    private slots:
            void onExpenseMenuClicked() const;
            void onChartsMenuClicked() const;
            void onRecurringMenuClicked() const;
            void onSettingsMenuClicked() const;
            void onMonthlyBudgetMenuClicked() const;

    private:
        void setupMenu();

        void createActions();
        void createMenuBar();
        void setupCategoryTool();
        void createTrayIcon();
    };
}

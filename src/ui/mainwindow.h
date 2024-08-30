#pragma once


#include <QMainWindow>
#include <qstackedwidget.h>
#include <qsystemtrayicon.h>

#include "expenses/expensemodel.h"
#include "recurring_expenses/recurringexpensesoverview.h"

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

    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class LSMainWindow;
    }

    QT_END_NAMESPACE

    class LSMainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        void setupMenu();


        explicit LSMainWindow(expenses::LSExpenseModel* expenseModel, QAbstractProxyModel* recurringModel, shared::LSDateController* dateController, expenses::LSRelatedExpenseProxyModel* relatedExpenseProxyModel, fa::QtAwesome* qtAwesome);

        void createActions();

        void createTrayIcon();

        ~LSMainWindow() override;

    private:
        Ui::LSMainWindow *ui;
        fa::QtAwesome * m_qtAwesome;

        int m_expensesIndex{};
        expenses::LSExpenseModel* m_expenseModel;
        expenses::LSExpensesOverviewWidget* m_expensesOverviewWidget;

        int m_recurringExpensesWidgetIndex{};
        QAbstractProxyModel* m_recurringExpensesProxyModel;
        expenses::LSRecurringExpensesOverview* m_recurringExpensesWidget;

        int m_chartsIndex{};
        QWidget * m_chartsWidget;

        shared::LSDateController * m_dateController;

        // System tray icon and menu
        QSystemTrayIcon *   trayIcon{};
        QAction *           minimizeAction{};
        QAction *           maximizeAction{};
        QAction *           restoreAction{};
        QAction *           quitAction{};
        QMenu*              trayIconMenu{};

        void setupToolbox();

    private slots:
            void onExpenseMenuClicked();
            void onChartsMenuClicked();
            void onRecurringMenuClicked();
    };
}

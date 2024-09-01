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
        explicit LSMainWindow(expenses::LSExpenseModel* expenseModel, QAbstractProxyModel* recurringModel, QAbstractProxyModel* categoryModel, shared::LSDateController* dateController, expenses::LSRelatedExpenseProxyModel* relatedExpenseProxyModel, fa::QtAwesome* qtAwesome);

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
        QAbstractProxyModel * m_categoryModel;

        // System tray icon and menu
        QSystemTrayIcon *   trayIcon{};
        QAction *           minimizeAction{};
        QAction *           maximizeAction{};
        QAction *           restoreAction{};
        QAction *           quitAction{};

        QMenu*              trayIconMenu{};
        QMenu *             m_helpMenu{};
        QMenu *             m_fileMenu{};

        void setupDateTool();

    private slots:
            void onExpenseMenuClicked() const;
            void onChartsMenuClicked() const;
            void onRecurringMenuClicked() const;

    private:
        void setupMenu();
        void createActions();
        void createMenuBar();
        void setupCategoryTool();
        void createTrayIcon();
    };
}

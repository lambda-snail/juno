#pragma once


#include <QMainWindow>
#include <qstackedwidget.h>
#include <qsystemtrayicon.h>

#include "expenses/expensemodel.h"

namespace fa
{
    class QtAwesome;
}

namespace LambdaSnail::Juno
{
    namespace expenses
    {
        class LSExpensesOverviewWidget;
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

        explicit LSMainWindow(expenses::LSExpenseModel *expenseModel, fa::QtAwesome* qtAwesome);

        void createActions();

        void createTrayIcon();

        ~LSMainWindow() override;

    private:
        Ui::LSMainWindow *ui;
        fa::QtAwesome * m_qtAwesome;

        int m_expensesIndex{};
        expenses::LSExpenseModel *m_expenseModel;
        expenses::LSExpensesOverviewWidget *expensesOverviewWidget;

        int m_chartsIndex{};
        QWidget * chartsWidget;

        // System tray icon and menu
        QSystemTrayIcon *   trayIcon{};
        QAction *           minimizeAction{};
        QAction *           maximizeAction{};
        QAction *           restoreAction{};
        QAction *           quitAction{};
        QMenu*              trayIconMenu{};


    private slots:
            void onExpenseMenuClicked();
            void onChartsMenuClicked();
            void onRecurringMenuClicked();
    };
}

#pragma once


#include <QMainWindow>
#include <qstackedwidget.h>

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

        ~LSMainWindow() override;

    private:
        Ui::LSMainWindow *ui;
        fa::QtAwesome * m_qtAwesome;

        int m_expensesIndex{};
        expenses::LSExpenseModel *m_expenseModel;
        expenses::LSExpensesOverviewWidget *expensesOverviewWidget;

        int m_chartsIndex{};
        QWidget * chartsWidget;

    private slots:
            void onExpenseMenuClicked();
            void onChartsMenuClicked();
    };
}

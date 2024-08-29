#pragma once

#include <QWidget>

class QDataWidgetMapper;

namespace LambdaSnail::Juno::expenses
{
    class LSRecurringExpenseModel;
}

namespace LambdaSnail::Juno::expenses
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class RecurringExpensesOverview;
    }

    QT_END_NAMESPACE

    class LSRecurringExpensesOverview : public QWidget
    {
        Q_OBJECT

    public:
        void setUpMapper();

        explicit LSRecurringExpensesOverview(QWidget *parent, LSRecurringExpenseModel* recurringModel);

        ~LSRecurringExpensesOverview() override;

    private:
        Ui::RecurringExpensesOverview* ui;

        LSRecurringExpenseModel* m_recurringModel;
        QDataWidgetMapper* m_mapper;
    };
}

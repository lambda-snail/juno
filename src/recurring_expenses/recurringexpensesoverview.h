#pragma once

#include <qabstractproxymodel.h>
#include <QWidget>

class QAbstractProxyModel;
class QDataWidgetMapper;

namespace LambdaSnail::Juno::expenses
{
    class LSRelatedExpenseProxyModel;
    class LSRecurringExpenseModel;

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

        void setUpRecurringExpensesView();

        void setUpRelatedExpensesView();

        explicit LSRecurringExpensesOverview(QWidget *parent, LSRelatedExpenseProxyModel* expenseModel, LSRecurringExpenseModel* recurringModel);

        ~LSRecurringExpensesOverview() override;

    private:
        Ui::RecurringExpensesOverview* ui;

        LSRecurringExpenseModel* m_recurringModel;
        LSRelatedExpenseProxyModel* m_expenseModel;
        QDataWidgetMapper* m_mapper{};
    };
}

#pragma once

#include <qabstractproxymodel.h>
#include <QWidget>

namespace LambdaSnail::Juno::shared
{
    class LSDateController;
}

namespace fa
{
    class QtAwesome;
}

class QAbstractProxyModel;
class QDataWidgetMapper;

namespace LambdaSnail::Juno::expenses
{
    class LSDateFromStringDelegate;
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

        explicit LSRecurringExpensesOverview(QWidget *parent, LSRelatedExpenseProxyModel* expensesProxyModel, QAbstractProxyModel* recurringModel, shared::LSDateController* dateController, fa::QtAwesome *qtAwesome);

        ~LSRecurringExpensesOverview() override;

    private:
        Ui::RecurringExpensesOverview* ui;

        shared::LSDateController* m_dateController;
        std::unique_ptr<LSDateFromStringDelegate> m_dateColumnDelegate;

        QAbstractProxyModel* m_recurringModel;
        LSRelatedExpenseProxyModel* m_expensesProxyModel;
        QDataWidgetMapper* m_mapper{};
        fa::QtAwesome* m_qtAwesome;
    };
}

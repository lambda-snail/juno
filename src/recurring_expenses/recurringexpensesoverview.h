#pragma once

#include "recurring_expenses/recurringexpensemodel.h"
#include "recurring_expenses/relatedexpenseproxymodel.h"
#include "shared/datecontroller.h"
#include "shared/date_time/datefromstringdelegate.h"

#include "QtAwesome.h"

#include <QAbstractProxyModel>
#include <QDataWidgetMapper>
#include <QWidget>

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

        void setUpRecurringExpensesView();

        void setUpRelatedExpensesView();

        explicit LSRecurringExpensesOverview(QWidget *parent, LSRelatedExpenseProxyModel* expensesProxyModel, QAbstractProxyModel* recurringModel, shared::LSDateController* dateController, QSettings* settings, fa::QtAwesome *qtAwesome);

        ~LSRecurringExpensesOverview() override;

    private:
        Ui::RecurringExpensesOverview* ui;

        shared::LSDateController* m_dateController;
        std::unique_ptr<shared::LSDateFromStringDelegate> m_dateColumnDelegate;

        QAbstractProxyModel* m_recurringModel;
        LSRelatedExpenseProxyModel* m_expensesProxyModel;
        QDataWidgetMapper* m_mapper{};

        QSettings* m_settings;
        fa::QtAwesome* m_qtAwesome;
    };
}

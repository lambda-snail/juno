#pragma once

#include "recurring_expenses/relatedexpenseproxymodel.h"
#include "shared/datecontroller.h"
#include "shared/date_time/datefromstringdelegate.h"

#include "QtAwesome.h"

#include <QDataWidgetMapper>
#include <QWidget>
#include <ui_recurringexpensesoverview.h>

#include "expenses/categoryfiltermodel.h"
#include "expenses/expensetoolbarfactory.h"
#include "shared/delegates/relationalproxydelegate.h"

namespace LambdaSnail::Juno::expenses
{
    // QT_BEGIN_NAMESPACE
    //
    // namespace Ui
    // {
    //     class RecurringExpensesOverview;
    // }
    //
    // QT_END_NAMESPACE

    class LSRecurringExpensesOverview : public QWidget
    {
        Q_OBJECT

    public:
        explicit LSRecurringExpensesOverview(QWidget *parent, LSRelatedExpenseProxyModel* expensesProxyModel, LSCategoryFilterModel* recurringModel, QAbstractProxyModel* categoryModel, shared::LSDateController* dateController, QSettings* settings, fa::QtAwesome *qtAwesome);
        ~LSRecurringExpensesOverview() override = default;

    private:
        std::unique_ptr<Ui::RecurringExpensesOverview> ui;

        shared::LSDateController* m_dateController;
        std::unique_ptr<ToolbarItems> m_toolBarItems;

        std::unique_ptr<shared::LSDateFromStringDelegate> m_dateColumnDelegate;
        std::unique_ptr<delegates::LSRelationalProxyDelegate> m_categoryColumnDelegate;
        std::unique_ptr<delegates::LSRelationalProxyDelegate> m_mapperDelegate;;

        LSCategoryFilterModel* m_recurringModel;
        LSRelatedExpenseProxyModel* m_expensesProxyModel;
        QAbstractProxyModel* m_categoryModel;
        QDataWidgetMapper* m_mapper{};

        QSettings* m_settings;
        fa::QtAwesome* m_qtAwesome;

        void setUpMapper();
        void setUpRecurringExpensesView();
        void setUpRelatedExpensesView();
    };
}

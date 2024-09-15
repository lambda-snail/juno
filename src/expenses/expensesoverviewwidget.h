#pragma once

#include "expenses/expensemodel.h"
#include "shared/date_time/datefromstringdelegate.h"

#include "QtAwesome.h"

#include <QDateTimeEdit>
#include <QPushButton>
#include <QSqlRelationalDelegate>
#include <QStatusBar>

#include "categoryfiltermodel.h"
#include "shared/delegates/relationalproxydelegate.h"

namespace LambdaSnail::Juno::expenses
{
    struct ToolbarItems;

    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class ExpensesOverviewWidget;
    }

    QT_END_NAMESPACE

    class LSExpensesOverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        LSExpensesOverviewWidget(QWidget* parent, QStatusBar* statusBar, LSExpenseModel* expenseModel, QAbstractProxyModel* categoryModel, QSettings* settings, fa::QtAwesome *qtAwesome);

        ~LSExpensesOverviewWidget() override;

    private:
        Ui::ExpensesOverviewWidget* ui;
        LSExpenseModel* m_expenseModel;
        LSCategoryFilterModel * m_categoryFilterModel;
        QAbstractProxyModel * m_categoryModel;

        std::unique_ptr<shared::LSDateFromStringDelegate> m_dateColumnDelegate;
        std::unique_ptr<delegates::LSRelationalProxyDelegate> m_categoryColumnDelegate;

        QStatusBar* m_statusBar;
        QSettings * m_settings;
        std::unique_ptr<ToolbarItems> m_toolBarItems;

        void setupTableView();

    private slots:
        // void onSearchDatesChanged();
        void onSelectionChanged(/*QItemSelection const &selected, QItemSelection const &deselected*/) const;
    };
}

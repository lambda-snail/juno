#pragma once

#include "expenses/expensemodel.h"
#include "shared/date_time/datefromstringdelegate.h"

#include "QtAwesome.h"

#include <QAbstractProxyModel>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QStatusBar>

namespace LambdaSnail::Juno::expenses
{
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
        LSExpensesOverviewWidget(QWidget *parent, QStatusBar *statusBar, LSExpenseModel *model, QAbstractProxyModel *categoryModel, fa::QtAwesome *qtAwesome);

        void setUpToolbar(fa::QtAwesome *qtAwesome);
        void setupTableView(LSExpenseModel* model);

        ~LSExpensesOverviewWidget() override;

    private:
        Ui::ExpensesOverviewWidget* ui;
        LSExpenseModel* m_expenseModel;
        QAbstractProxyModel * m_categoryModel;

        std::unique_ptr<shared::LSDateFromStringDelegate> m_dateColumnDelegate;

        QStatusBar* m_statusBar;

        // Command bar
        // QDateEdit* m_fromDate{};
        // QDateEdit* m_toDate{};
        QPushButton* m_searchButton{};
        QPushButton* m_deleteExpenseButton{};
        QPushButton* m_newExpenseButton{};

    private slots:
        // void onSearchDatesChanged();
        void onSelectionChanged(/*QItemSelection const &selected, QItemSelection const &deselected*/);
    };
}

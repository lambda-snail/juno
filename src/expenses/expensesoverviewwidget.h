#pragma once

#include "expenses/expensemodel.h"
#include "shared/date_time/datefromstringdelegate.h"

#include "QtAwesome.h"

#include <QAbstractProxyModel>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QSqlRelationalDelegate>
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
        LSExpensesOverviewWidget(QWidget *parent, QStatusBar *statusBar, QAbstractProxyModel *expenseModel, QAbstractProxyModel *categoryModel, QSettings* settings, fa::QtAwesome *qtAwesome);

        ~LSExpensesOverviewWidget() override;

    private:
        Ui::ExpensesOverviewWidget* ui;
        QAbstractProxyModel* m_expenseModel;
        QAbstractProxyModel * m_categoryModel;

        std::unique_ptr<shared::LSDateFromStringDelegate> m_dateColumnDelegate;

        QStatusBar* m_statusBar;
        QSettings * m_settings;

        // Command bar
        // QDateEdit* m_fromDate{};
        // QDateEdit* m_toDate{};
        QPushButton* m_searchButton{};
        QPushButton* m_deleteExpenseButton{};
        QPushButton* m_newExpenseButton{};

        void setUpToolbar(fa::QtAwesome *qtAwesome);
        void setupTableView(QAbstractProxyModel* model);

    private slots:
        // void onSearchDatesChanged();
        void onSelectionChanged(/*QItemSelection const &selected, QItemSelection const &deselected*/);
    };
}

#pragma once

#include <qdatetimeedit.h>
#include <qpushbutton.h>
#include <qstatusbar.h>

namespace LambdaSnail::Juno::expenses
{
    class LSExpenseModel;
}

namespace LambdaSnail::Juno::shared
{
    class LSDateFromStringDelegate;
}

namespace fa
{
    class QtAwesome;
}

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
        void setUpToolbar(fa::QtAwesome *qtAwesome);

        void setupTableView(LSExpenseModel* model);

        explicit LSExpensesOverviewWidget(QWidget* parent, QStatusBar* statusBar, LSExpenseModel* model, fa::QtAwesome* qtAwesome);

        ~LSExpensesOverviewWidget() override;

    private:
        Ui::ExpensesOverviewWidget* ui;
        LSExpenseModel* m_model;
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

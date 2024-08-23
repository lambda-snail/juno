#pragma once

#include <qdatetimeedit.h>
#include <qpushbutton.h>
#include <QWidget>

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
        void setUpToolbar();

        explicit LSExpensesOverviewWidget(QWidget* parent, class LSExpenseModel* model);

        ~LSExpensesOverviewWidget() override;

    private:
        Ui::ExpensesOverviewWidget* ui;
        LSExpenseModel* m_model;
        QDateEdit* fromDate;
        QDateEdit* toDate;
        QPushButton * searchButton;

    private slots:
        void onSearchDatesChanged();
    };
} // LambdaSnail::Juno::expenses

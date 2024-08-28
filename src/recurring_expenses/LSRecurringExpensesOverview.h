#pragma once

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
        explicit LSRecurringExpensesOverview(QWidget *parent = nullptr);

        ~LSRecurringExpensesOverview() override;

    private:
        Ui::RecurringExpensesOverview *ui;
    };
}

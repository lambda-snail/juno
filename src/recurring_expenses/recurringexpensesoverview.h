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

    class RecurringExpensesOverview : public QWidget
    {
        Q_OBJECT

    public:
        explicit RecurringExpensesOverview(QWidget *parent = nullptr);

        ~RecurringExpensesOverview() override;

    private:
        Ui::RecurringExpensesOverview *ui;
    };
}

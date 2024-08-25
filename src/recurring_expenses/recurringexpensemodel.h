#pragma once
#include <QSqlTableModel>

namespace LambdaSnail::Juno::expenses
{
    class RecurringExpenseModel : public QSqlTableModel
    {
        Q_OBJECT

    public:
        explicit RecurringExpenseModel() = default;

        void initialize();
        [[nodiscard]] static QSqlQuery tableDefinition();

        enum class Columns
        {
            id,
            activeFrom,
            activeTo,
            billingDay,
            billingMonth,
            recipient,
            description,
            category,
            amount,

            createdOn,
            modifiedOn
        };
    };
}


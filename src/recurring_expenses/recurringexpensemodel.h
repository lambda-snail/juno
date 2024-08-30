#pragma once
#include <QSqlTableModel>

namespace LambdaSnail::Juno::expenses
{
    class LSRecurringExpenseModel : public QSqlTableModel
    {
        Q_OBJECT

    public:
        explicit LSRecurringExpenseModel() = default;

        void initialize();
        [[nodiscard]] static QSqlQuery tableDefinition();

        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

        enum class Columns
        {
            id,
            activeFrom,
            activeTo,
            billingDay,
            recipient,
            description,
            category,
            amount,

            createdOn,
            modifiedOn
        };

        enum class Roles
        {
            IdRole = 0x0101
        };
    };
}


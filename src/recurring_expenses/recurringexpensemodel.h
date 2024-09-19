#pragma once

#include "shared/currency/expensemodelbase.h"

namespace LambdaSnail::Juno::expenses
{
    class LSRecurringExpenseModel : public LSExpenseModelBase
    {
        Q_OBJECT

    public:
        explicit LSRecurringExpenseModel() = default;

        void initialize();
        [[nodiscard]] static QSqlQuery tableDefinition();
        [[nodiscard]] bool isCurrencyColumn(QModelIndex const& index) const override;

        [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;

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


#pragma once

#include "shared/currency/expensemodelbase.h"

namespace LambdaSnail::Juno::expenses
{
    // TODO: Take date as params in ctor so that we don't query everything at once
    class LSExpenseModel : public LSExpenseModelBase
    {
    public:
        explicit LSExpenseModel() = default;

        void initialize();
        void setDateFilter(QDate from, QDate to);
        bool isCurrencyColumn(QModelIndex const& index) const override;

        [[nodiscard]] static QSqlQuery tableDefinition();

        enum class Columns
        {
            id,
            date,
            recipient,
            description,
            category,
            amount,
            relatedExpense,
            createdOn,
            modifiedOn
        };
    };
}

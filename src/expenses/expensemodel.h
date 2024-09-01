#pragma once

#include <QSqlRelationalTableModel>

namespace LambdaSnail::Juno::expenses
{
    // TODO: Take date as params in ctor so that we don't query everything at once
    class LSExpenseModel : public QSqlRelationalTableModel
    {
    public:
        explicit LSExpenseModel() = default;

        void initialize();
        void setDateFilter(QDate from, QDate to);

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

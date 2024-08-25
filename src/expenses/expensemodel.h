#pragma once

#include <QSqlTableModel>

namespace LambdaSnail::Juno::expenses
{
    // TODO: Take date as params in ctor so that we don't query everything at once
    class LSExpenseModel : public QSqlTableModel
    {
    public:
        LSExpenseModel();

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

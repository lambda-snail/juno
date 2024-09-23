#pragma once
#include <QSqlTableModel>

#include "shared/currency/expensemodelbase.h"

namespace LambdaSnail::Juno::categories
{
    class LSCategoryModel : public expenses::LSExpenseModelBase
    {
        Q_OBJECT

    public:
        void initialize();

        [[nodiscard]] static QSqlQuery tableDefinition();
        [[nodiscard]] static QSqlQuery insertDefaultData();
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;

        bool isCurrencyColumn(QModelIndex const& index) const override;

        enum class Columns
        {
            id,
            category,
            spending_limit
        };
    };
}

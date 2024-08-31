//
// Created by niclas on 8/31/24.
//

#include "aggregateexpensemodel.h"

#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno::expenses
{
    enum class Category
    {
        Subscription,
        DiningOut,
        Groceries
    };

    QVariant LSAggregateExpenseModel::data(const QModelIndex &index, int role) const
    {
        if(role != Qt::DisplayRole)
        {
            return {};
        }

        int32_t category = index.row();
        QString categoryString{};
        if(category == static_cast<int32_t>(Category::Groceries))
        {
            categoryString = "Groceries";
        }
        else if(category == static_cast<int32_t>(Category::Subscription))
        {
            categoryString = "Subscription";
        }
        else
        {
            categoryString = "Dining Out";
        }

        double sum = 0;
        for(int row = 0; row < sourceModel()->rowCount(); ++row)
        {
            QModelIndex categoryIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::category));
            QString const rowCategory = sourceModel()->data(categoryIndex, role).toString();
            if(rowCategory == categoryString)
            {
                QModelIndex amountIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::amount));
                sum += sourceModel()->data(amountIndex, role).toInt();
            }
        }

        return sum;
    }

    int LSAggregateExpenseModel::rowCount(const QModelIndex &parent) const
    {
        return 3; // num categories
    }

    int LSAggregateExpenseModel::columnCount(const QModelIndex &parent) const
    {
        return 1;
    }
}

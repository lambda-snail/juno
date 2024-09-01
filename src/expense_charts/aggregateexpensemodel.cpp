#include "aggregateexpensemodel.h"

#include "categories/categorymodel.h"
#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno::expenses
{
    LSAggregateExpenseModel::LSAggregateExpenseModel(QAbstractProxyModel* categories, QObject *parent) :
        QIdentityProxyModel(parent),
        m_categories(categories)
    {
        connect(m_categories, &QAbstractItemModel::dataChanged, this, &LSAggregateExpenseModel::dataChanged);
    }

    QVariant LSAggregateExpenseModel::data(const QModelIndex &index, int role) const
    {
        if(role != Qt::DisplayRole)
        {
            return {};
        }

        int32_t const category = getCategoryKey(index, role);

        double sum = 0;
        for(int row = 0; row < sourceModel()->rowCount(); ++row)
        {
            if(getRowCategory(role, row) == category)
            {
                QModelIndex amountIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::amount));
                sum += sourceModel()->data(amountIndex, role).toInt();
            }
        }

        return sum;
    }

    int32_t LSAggregateExpenseModel::getCategoryKey(const QModelIndex &index, int role) const
    {
        QModelIndex categoryIndex = m_categories->index(index.row(), static_cast<int>(categories::LSCategoryModel::Columns::id));
        return m_categories->data(categoryIndex, role).toInt();
    }

    int32_t LSAggregateExpenseModel::getRowCategory(int role, int row) const
    {
        QModelIndex categoryIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::category));
        return sourceModel()->data(categoryIndex, role).toInt();
    }

    int LSAggregateExpenseModel::rowCount(const QModelIndex &parent) const
    {
        return m_categories->rowCount();
    }

    int LSAggregateExpenseModel::columnCount(const QModelIndex &parent) const
    {
        return 1;
    }
}

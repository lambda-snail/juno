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
        if(role != Qt::DisplayRole and role != Roles::CategoryRole)
        {
            return {};
        }

        QVariant const category = getCategoryKey(index, Qt::DisplayRole);
        QString categoryAsString = category.toString();

        if(role == Roles::CategoryRole)
        {
            return categoryAsString;
        }

        double sum = 0;
        for(int row = 0; row < sourceModel()->rowCount(); ++row)
        {
            QVariant const rowCategory = getRowCategory(role, row);

            // We compare the strings of the category name as a workaround for now,
            // as the relational table model hides the underlying key
            if(rowCategory.toString() == categoryAsString)
            {
                QModelIndex amountIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::amount));
                sum += sourceModel()->data(amountIndex, role).toInt();
            }
        }

        return sum;
    }

    QVariant LSAggregateExpenseModel::getCategoryKey(const QModelIndex &index, int role) const
    {
        QModelIndex categoryIndex = m_categories->index(index.row(), static_cast<int>(categories::LSCategoryModel::Columns::category));
        return m_categories->data(categoryIndex, role);
    }

    QVariant LSAggregateExpenseModel::getRowCategory(int role, int row) const
    {
        QModelIndex categoryIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::category));
        return sourceModel()->data(categoryIndex, role);
    }

    int LSAggregateExpenseModel::rowCount(const QModelIndex &parent) const
    {
        return m_categories->rowCount();
    }

    int LSAggregateExpenseModel::columnCount(const QModelIndex &parent) const
    {
        return 1;
    }

    bool operator==(int lhs, LSAggregateExpenseModel::Roles rhs)
    {
        return lhs == static_cast<int32_t>(rhs);
    }
}

#include "aggregateexpensemodel.h"

#include "categories/categorymodel.h"
#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno::expenses
{
    enum class Category
    {
        Subscription,
        DiningOut,
        Groceries
    };

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

        // int32_t category = index.row();
        // QString categoryString{};

        QModelIndex categoryIndex = m_categories->index(index.row(), static_cast<int>(categories::LSCategoryModel::Columns::category));
        QString category = m_categories->data(categoryIndex, role).toString();

        qDebug() << category;

        double sum = 0;
        for(int row = 0; row < sourceModel()->rowCount(); ++row)
        {
            QModelIndex categoryIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::category));
            QString const rowCategory = sourceModel()->data(categoryIndex, role).toString();
            if(rowCategory == category)
            {
                QModelIndex amountIndex = sourceModel()->index(row, static_cast<int>(LSExpenseModel::Columns::amount));
                sum += sourceModel()->data(amountIndex, role).toInt();
            }
        }

        return sum;
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

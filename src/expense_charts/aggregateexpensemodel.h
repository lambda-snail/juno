#pragma once

#include <QIdentityProxyModel>

namespace LambdaSnail::Juno::categories
{
    class LSCategoryModel;
}

namespace LambdaSnail::Juno::expenses
{
    class LSAggregateExpenseModel : public QIdentityProxyModel
    {
        Q_OBJECT

    public:
        explicit LSAggregateExpenseModel(QAbstractProxyModel* categories, QObject *parent = nullptr);

        [[nodiscard]] QVariant getCategoryKey(const QModelIndex &index, int role) const;
        [[nodiscard]] QVariant getRowCategory(int role, int row) const;

        /**
         * Accepts either Qt::DisplayRole or Roles::CategoryRole. The former will aggregate all expenses of the category
         * given by index.row(), while the later will yield the name of the category index.row() as a QString.
         */
        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
        [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

        enum class Roles
        {
            /**
             * Passing the CategoryRole to an aggregate expense model will return the name of the category in a QVariant.
             */
            CategoryRole = Qt::UserRole
        };
    private:
        QAbstractProxyModel* m_categories;
    };

    bool operator==(int lhs, LSAggregateExpenseModel::Roles rhs);
}

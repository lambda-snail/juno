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

        QVariant getCategoryKey(const QModelIndex &index, int role) const;

        QVariant getRowCategory(int role, int row) const;

        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
        [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    private:
        QAbstractProxyModel* m_categories;
    };
}

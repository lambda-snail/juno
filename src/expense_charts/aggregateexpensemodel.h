#pragma once
#include <QIdentityProxyModel>

namespace LambdaSnail::Juno::expenses
{
    class LSAggregateExpenseModel : public QIdentityProxyModel
    {
        Q_OBJECT

    public:
        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
        [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
    };
}

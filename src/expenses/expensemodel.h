#pragma once

#include <QAbstractTableModel>

namespace LambdaSnail::Juno::expenses
{
    class ExpenseModel : QAbstractTableModel
    {
    public:
        [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    };
}

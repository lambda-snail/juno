#include "expensemodelbase.h"

namespace LambdaSnail::Juno::expenses
{
    QVariant LSExpenseModelBase::data(const QModelIndex &index, int role) const
    {
        if((role == Qt::DisplayRole or role == Qt::EditRole) and isCurrencyColumn(index))
        {
            int32_t integerAmount = QSqlRelationalTableModel::data(index, role).toInt();
            return { static_cast<double>(integerAmount) / IntToDoubleConversionFactor };
        }

        return QSqlRelationalTableModel::data(index, role);
    }

    bool LSExpenseModelBase::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if(role == Qt::EditRole and isCurrencyColumn(index))
        {
            return QSqlRelationalTableModel::setData(index, value.toInt() * IntToDoubleConversionFactor, role);
        }

        return QSqlRelationalTableModel::setData(index, value, role);
    }
}

#pragma once

#include <QSqlRelationalTableModel>

namespace LambdaSnail::Juno::expenses
{
    /**
     * Base class for sql models that have at least one currency column.
     */
    class LSExpenseModelBase : public QSqlRelationalTableModel
    {
    public:

        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
        [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;

        /**
         * 
         * @param index Returns true if the model index represents a value with currency semantics.
         */
        [[nodiscard]] virtual bool isCurrencyColumn(QModelIndex const& index) const =0;

        static constexpr int32_t IntToDoubleConversionFactor = 100;
    };
}

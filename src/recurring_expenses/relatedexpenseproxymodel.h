#pragma once

#include <QSortFilterProxyModel>

namespace LambdaSnail::Juno::expenses
{
    class RelatedExpenseProxyModel : public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(int32_t m_relatedExpense READ relatedExpense WRITE setRelatedExpense)

    public:
        explicit RelatedExpenseProxyModel(QObject* parent = nullptr);

        [[nodiscard]] bool filterAcceptsRow(int sourceRow, QModelIndex const& sourceParent) const override;

        [[nodiscard]] int32_t relatedExpense() const;
        void setRelatedExpense(int32_t relatedExpense);


    private:
        int32_t m_relatedExpense{};
    };
}

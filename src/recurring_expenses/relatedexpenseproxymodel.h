#pragma once

#include <QSortFilterProxyModel>

namespace LambdaSnail::Juno::expenses
{
    /**
     * Filer to display expenses related to a recurring expense.
     */
    class LSRelatedExpenseProxyModel : public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(int32_t m_relatedExpense READ relatedExpense WRITE setRelatedExpense)
        Q_PROPERTY(bool m_isActive READ isActive WRITE setIsActive)

    public:
        explicit LSRelatedExpenseProxyModel(QObject* parent = nullptr);

        [[nodiscard]] bool filterAcceptsRow(int sourceRow, QModelIndex const& sourceParent) const override;

        [[nodiscard]] int32_t relatedExpense() const;
        void setRelatedExpense(int32_t relatedExpense);

        [[nodiscard]] bool isActive() const;
        void setIsActive(bool isActive);

    private:
        bool m_isActive{};
        int32_t m_relatedExpense{};
    };
}

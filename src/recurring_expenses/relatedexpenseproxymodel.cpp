#include "relatedexpenseproxymodel.h"

#include "expenses/expensemodel.h"

namespace LS = LambdaSnail::Juno::expenses;

LS::RelatedExpenseProxyModel::RelatedExpenseProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

bool LambdaSnail::Juno::expenses::RelatedExpenseProxyModel::filterAcceptsRow(int sourceRow, QModelIndex const& sourceParent) const
{
    if(not m_isActive)
    {
        return false;
    }

    QModelIndex const sourceIndex = sourceModel()->index(sourceRow, static_cast<int>(LSExpenseModel::Columns::relatedExpense), sourceParent);
    QVariant const relatedExpense = sourceIndex.data();
    return relatedExpense.isValid() and relatedExpense.value<int32_t>() == m_relatedExpense;
}

int32_t LambdaSnail::Juno::expenses::RelatedExpenseProxyModel::relatedExpense() const
{
    return m_relatedExpense;
}

void LambdaSnail::Juno::expenses::RelatedExpenseProxyModel::setRelatedExpense(int32_t relatedExpense)
{
    if(m_relatedExpense != relatedExpense)
    {
        m_relatedExpense = relatedExpense;
        invalidateFilter();
    }
}

bool LambdaSnail::Juno::expenses::RelatedExpenseProxyModel::isActive() const
{
    return m_isActive;
}

void LambdaSnail::Juno::expenses::RelatedExpenseProxyModel::setIsActive(bool isActive)
{
    if(m_isActive != isActive)
    {
        m_isActive = isActive;
        invalidateFilter();
    }
}

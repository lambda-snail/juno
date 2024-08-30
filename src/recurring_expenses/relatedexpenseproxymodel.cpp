#include "relatedexpenseproxymodel.h"

#include "expenses/expensemodel.h"

namespace LS = LambdaSnail::Juno::expenses;

LS::LSRelatedExpenseProxyModel::LSRelatedExpenseProxyModel(QObject *parent) : QSortFilterProxyModel(parent), m_isActive(false) {}

bool LambdaSnail::Juno::expenses::LSRelatedExpenseProxyModel::filterAcceptsRow(int sourceRow, QModelIndex const& sourceParent) const
{
    if(not m_isActive)
    {
        return false;
    }

    QModelIndex const sourceIndex = sourceModel()->index(sourceRow, static_cast<int>(LSExpenseModel::Columns::relatedExpense), sourceParent);
    QVariant const relatedExpense = sourceIndex.data();
    return relatedExpense.isValid() and relatedExpense.value<int32_t>() == m_relatedExpense;
}

int32_t LambdaSnail::Juno::expenses::LSRelatedExpenseProxyModel::relatedExpense() const
{
    return m_relatedExpense;
}

void LambdaSnail::Juno::expenses::LSRelatedExpenseProxyModel::setRelatedExpense(int32_t relatedExpense)
{
    if(m_relatedExpense != relatedExpense)
    {
        beginResetModel();
        m_isActive = true;
        m_relatedExpense = relatedExpense;
        endResetModel();
    }
}

bool LambdaSnail::Juno::expenses::LSRelatedExpenseProxyModel::isActive() const
{
    return m_isActive;
}

void LambdaSnail::Juno::expenses::LSRelatedExpenseProxyModel::setIsActive(bool isActive)
{
    if(m_isActive != isActive)
    {
        beginResetModel();
        m_isActive = isActive;
        endResetModel();
    }
}

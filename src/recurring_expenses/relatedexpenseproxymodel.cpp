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

    QVariant const relatedExpense = sourceModel()->index(sourceRow, static_cast<int>(LSExpenseModel::Columns::relatedExpense), sourceParent).data();

    // To display newly created rows in the view, we use the heuristic that expenses lacking an amount are 'under construction'
    // If this is removed, new rows will not be added to the model
    QVariant const amount = sourceModel()->index(sourceRow, static_cast<int>(LSExpenseModel::Columns::amount), sourceParent).data();

    return (relatedExpense.isValid() and relatedExpense.value<int32_t>() == m_relatedExpense) or (amount.isValid() and amount.toInt() == 0);
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

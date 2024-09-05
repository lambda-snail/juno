#include "categoryfiltermodel.h"

namespace LambdaSnai::Juno::expenses
{
    LSCategoryFilterModel::LSCategoryFilterModel(QObject* parent, int categoryColumn) :
        QSortFilterProxyModel(parent),
        m_categoryColumn(categoryColumn),
        m_filterCategory(0) { }

    bool LSCategoryFilterModel::filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const
    {
        if(not m_isActive)
        {
            return true;
        }

        QVariant const category = sourceModel()->index(sourceRow, m_categoryColumn, sourceParent).data();
        return category.toInt() == m_filterCategory;
    }

    bool LSCategoryFilterModel::isActive() const
    {
        return m_isActive;
    }

    void LSCategoryFilterModel::setIsActive(bool isActive)
    {
        m_isActive = isActive;
    }

    bool LSCategoryFilterModel::filterCategory() const
    {
        return m_filterCategory;
    }

    void LSCategoryFilterModel::setFilterCategory(int32_t category)
    {
        if(category != m_filterCategory)
        {
            beginResetModel();
            m_isActive = true;
            m_filterCategory = category;
            endResetModel();
        }
    }
}

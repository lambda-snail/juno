#include "categoryfiltermodel.h"

namespace LambdaSnail::Juno::expenses
{
    LSCategoryFilterModel::LSCategoryFilterModel(QObject* parent, int categoryColumn) :
        QSortFilterProxyModel(parent),
        m_categoryColumn(categoryColumn) { }

    bool LSCategoryFilterModel::filterAcceptsRow(int sourceRow, QModelIndex const &sourceParent) const
    {
        if(not m_isActive)
        {
            return true;
        }

        QVariant const category = sourceModel()->index(sourceRow, m_categoryColumn, sourceParent).data();
        return category.toString() == m_filterCategory;
    }

    bool LSCategoryFilterModel::isActive() const
    {
        return m_isActive;
    }

    void LSCategoryFilterModel::setInactive()
    {
        setFilterCategory({});
    }

    QStringView LSCategoryFilterModel::filterCategory() const
    {
        return m_filterCategory;
    }

    void LSCategoryFilterModel::setFilterCategory(QStringView const category)
    {
        if(category != m_filterCategory)
        {
            beginResetModel();
            m_isActive = not category.isEmpty();
            m_filterCategory = category;
            endResetModel();
        }
    }
}

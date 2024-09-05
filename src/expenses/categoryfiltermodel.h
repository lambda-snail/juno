#pragma once

#include <QSortFilterProxyModel>

namespace LambdaSnai::Juno::expenses
{
    class LSCategoryFilterModel : public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(int32_t m_filterCategory READ filterCategory WRITE setFilterCategory)
        Q_PROPERTY(bool m_isActive READ isActive WRITE setIsActive)

    public:
        explicit LSCategoryFilterModel(QObject* parent, int categoryColumn);

        [[nodiscard]] bool filterAcceptsRow(int sourceRow, QModelIndex const& sourceParent) const override;

        [[nodiscard]] bool isActive() const;
        void setIsActive(bool isActive);

        [[nodiscard]] bool filterCategory() const;
        void setFilterCategory(int32_t category);

    private:
        int32_t m_categoryColumn;

        int32_t m_filterCategory;
        bool m_isActive = false;
    };
}

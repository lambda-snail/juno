#pragma once

#include <QSortFilterProxyModel>

namespace LambdaSnail::Juno::expenses
{
    class LSCategoryFilterModel : public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(QStringView m_filterCategory READ filterCategory WRITE setFilterCategory)
        Q_PROPERTY(bool m_isActive READ isActive)

    public:
        explicit LSCategoryFilterModel(QObject* parent, int categoryColumn);

        [[nodiscard]] bool filterAcceptsRow(int sourceRow, QModelIndex const& sourceParent) const override;

        [[nodiscard]] bool isActive() const;
        void setInactive();

        [[nodiscard]] QStringView filterCategory() const;
        void setFilterCategory(QStringView const category);

    private:
        int32_t m_categoryColumn;

        QStringView m_filterCategory;
        bool m_isActive = false;
    };
}

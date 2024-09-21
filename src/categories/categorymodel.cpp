#include "categorymodel.h"

#include <QSqlQuery>

namespace LambdaSnail::Juno::categories
{
    void LSCategoryModel::initialize()
    {
        setTable("categories");

        setHeaderData(static_cast<int>(Columns::id), Qt::Horizontal, QObject::tr("Id"));
        setHeaderData(static_cast<int>(Columns::category), Qt::Horizontal, QObject::tr("Category"));
        setHeaderData(static_cast<int>(Columns::spending_limit), Qt::Horizontal, QObject::tr("Budget Limit"));

        select();
    }

    QSqlQuery LSCategoryModel::tableDefinition()
    {
        return QSqlQuery(R"(
            create table categories (
                id integer primary key,
                category varchar(256),
                spending_limit int default 0 not null

                unique(category)
            );
        )");
    }

    QSqlQuery LSCategoryModel::insertDefaultData()
    {
        return QSqlQuery("insert into categories values (0, 'Uncategorized', 0)");
    }

    bool LSCategoryModel::isCurrencyColumn(QModelIndex const &index) const
    {
        return index.column() == static_cast<uint32_t>(Columns::spending_limit);
    }
}

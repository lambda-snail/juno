#include "categorymodel.h"

#include <QSqlQuery>

namespace LambdaSnail::Juno::categories
{
    void LSCategoryModel::initialize()
    {
        setTable("categories");

        setHeaderData(static_cast<int>(Columns::id), Qt::Horizontal, QObject::tr("Id"));
        setHeaderData(static_cast<int>(Columns::category), Qt::Horizontal, QObject::tr("Category"));

        select();
    }

    QSqlQuery LSCategoryModel::tableDefinition()
    {
        return QSqlQuery(R"(
            create table categories (
                id integer primary key,
                category varchar(256),

                unique(category)
            );
        )");
    }
}

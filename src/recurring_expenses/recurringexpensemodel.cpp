#include "recurringexpensemodel.h"

#include <QSqlQuery>

namespace LS = LambdaSnail::Juno::expenses;

void LS::RecurringExpenseModel::initialize()
{
}

QSqlQuery LambdaSnail::Juno::expenses::RecurringExpenseModel::tableDefinition()
{
    return QSqlQuery(R"(
            create table expenses (
                id integer primary key,
                activeFrom varchar(10),
                activeTo varchar(10),
                billingDay integer,
                billingMonth integer,
                recipient text,
                description text,
                category text,
                amount integer,

                createdon integer,
                modifiedon integer
            )
        )");
}

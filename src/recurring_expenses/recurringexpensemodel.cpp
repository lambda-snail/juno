#include "recurringexpensemodel.h"

#include <QSqlQuery>

namespace LS = LambdaSnail::Juno::expenses;

void LS::LSRecurringExpenseModel::initialize()
{
}

QSqlQuery LS::LSRecurringExpenseModel::tableDefinition()
{
    return QSqlQuery(R"(
            create table recurring_expenses (
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
            );
        )");
}

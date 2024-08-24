#include "expensemodel.h"

#include <QDate>
#include <QSqlQuery>

#include "shared/database_manager.h"

namespace LS = LambdaSnail::Juno::expenses;

// setFilter

LS::LSExpenseModel::LSExpenseModel() : QSqlTableModel()
{
}

void LS::LSExpenseModel::initialize()
{
    setTable("expenses");

    setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
}

void LS::LSExpenseModel::setDateFilter(QDate const from, QDate const to)
{
    std::string const where = std::format("date >= '{}' and date <= '{}'", from.toString("yyyy-MM-dd").toStdString(),
                                          to.toString("yyyy-MM-dd").toStdString());
    setFilter(where.data());
    select();
}

QSqlQuery LambdaSnail::Juno::expenses::LSExpenseModel::tableDefinition()
{
    return QSqlQuery(R"(
            create table expenses (
                id integer primary key,
                date varchar(10),
                recipient text,
                description text,
                category text,
                amount integer,

                createdon integer,
                modifiedon integer
            )
        )");
}

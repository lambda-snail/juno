#include "expensemodel.h"

#include <QDate>
#include <QSqlQuery>

namespace LS = LambdaSnail::Juno::expenses;

void LS::LSExpenseModel::initialize()
{
    setTable("expenses");

    setRelation(static_cast<int>(Columns::category), QSqlRelation("categories", "id", "category"));

    setHeaderData(static_cast<int>(Columns::date), Qt::Horizontal, QObject::tr("Date"));
    setHeaderData(static_cast<int>(Columns::recipient), Qt::Horizontal, QObject::tr("Recipient"));
    setHeaderData(static_cast<int>(Columns::category), Qt::Horizontal, QObject::tr("Category"));
    setHeaderData(static_cast<int>(Columns::description), Qt::Horizontal, QObject::tr("Description"));
    setHeaderData(static_cast<int>(Columns::amount), Qt::Horizontal, QObject::tr("Amount"));
}

void LS::LSExpenseModel::setDateFilter(QDate const from, QDate const to)
{
    beginResetModel();

    // Dates in the DB are not affected by format from settings
    std::string const where = std::format("date >= '{}' and date <= '{}'", from.toString("yyyy-MM-dd").toStdString(),
                                          to.toString("yyyy-MM-dd").toStdString());

    qDebug() << where;

    setFilter(where.data());
    select();

    endResetModel();
}

QSqlQuery LS::LSExpenseModel::tableDefinition()
{
    return QSqlQuery(R"(
            create table expenses (
                id integer primary key,
                date varchar(10),
                recipient text,
                description text,
                category integer,
                amount integer,

                related_expense integer,
                createdon integer,
                modifiedon integer,

                foreign key(related_expense) references recurring_expenses(id)
                foreign key(category) references categories(id)
            );
        )");
}

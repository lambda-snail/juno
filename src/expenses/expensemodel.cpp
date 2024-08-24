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
    std::string const where = std::format("date >= '{}' and date <= '{}'", from.toString("yyyy-MM-dd").toStdString(), to.toString("yyyy-MM-dd").toStdString());
    setFilter(where.data());
    select();
}

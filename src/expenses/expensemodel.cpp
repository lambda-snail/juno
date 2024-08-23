#include "expensemodel.h"

#include <QDate>
#include <QSqlQuery>

namespace LS = LambdaSnail::Juno::expenses;

// setFilter

LS::LSExpenseModel::LSExpenseModel() : QSqlTableModel()
{

}

void LS::LSExpenseModel::initialize()
{
    setTable("expenses");
    select();
}

void LS::LSExpenseModel::setDateFilter(QDate const from, QDate const to)
{
    std::string const where = std::format("date >= '{}' and date <= '{}'", from.toString("yyyy-MM-dd").toStdString(), to.toString("yyyy-MM-dd").toStdString());
    setFilter(where.data());
    select();
}

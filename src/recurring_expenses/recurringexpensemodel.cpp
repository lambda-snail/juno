#include "recurringexpensemodel.h"

#include <QSqlQuery>
#include <QSqlRecord>

namespace LS = LambdaSnail::Juno::expenses;

void LS::LSRecurringExpenseModel::initialize()
{
    setTable("recurring_expenses");

    setRelation(static_cast<int>(Columns::category), QSqlRelation("categories", "id", "category"));

    setHeaderData(static_cast<int>(Columns::recipient), Qt::Horizontal, QObject::tr("Recipient"));
    setHeaderData(static_cast<int>(Columns::amount), Qt::Horizontal, QObject::tr("Amount"));
    setHeaderData(static_cast<int>(Columns::category), Qt::Horizontal, QObject::tr("Category"));
    setHeaderData(static_cast<int>(Columns::description), Qt::Horizontal, QObject::tr("Description"));
    setHeaderData(static_cast<int>(Columns::id), Qt::Horizontal, QObject::tr("Id"));
    setHeaderData(static_cast<int>(Columns::activeFrom), Qt::Horizontal, QObject::tr("Active From"));
    setHeaderData(static_cast<int>(Columns::activeTo), Qt::Horizontal, QObject::tr("Active To"));
    setHeaderData(static_cast<int>(Columns::billingDay), Qt::Horizontal, QObject::tr("Billing Day"));
    setHeaderData(static_cast<int>(Columns::createdOn), Qt::Horizontal, QObject::tr("Created On"));
    setHeaderData(static_cast<int>(Columns::modifiedOn), Qt::Horizontal, QObject::tr("Modified On"));

    select();
}

QSqlQuery LS::LSRecurringExpenseModel::tableDefinition()
{
    return QSqlQuery(R"(
            create table recurring_expenses (
                id integer primary key,
                activeFrom varchar(10),
                activeTo varchar(10),
                billingDay integer,
                recipient text,
                description text,
                category text,
                amount integer,

                createdon integer,
                modifiedon integer
            );
        )");
}

bool LambdaSnail::Juno::expenses::LSRecurringExpenseModel::isCurrencyColumn(QModelIndex const &index) const
{
    return index.column() == static_cast<int32_t>(Columns::amount);
}


QVariant LambdaSnail::Juno::expenses::LSRecurringExpenseModel::data(const QModelIndex &index, int role) const
{
    if(role == static_cast<int>(Roles::IdRole))
    {
        return record(index.row()).value(static_cast<int>(Columns::id));
    }

    return LSExpenseModelBase::data(index, role);
}

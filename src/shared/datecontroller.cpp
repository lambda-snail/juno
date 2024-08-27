#include "datecontroller.h"

#include "expenses/expensemodel.h"

namespace LS = LambdaSnail::Juno::shared;

LambdaSnail::Juno::shared::LSDateController::LSDateController(expenses::LSExpenseModel &model, QObject *parent) : QObject(parent), m_model(model) {}

void LambdaSnail::Juno::shared::LSDateController::updateDateLimits() const
{
    m_model.setDateFilter(m_fromDate, m_toDate);
}

QDate LS::LSDateController::getFromDate() const
{
    return m_fromDate;
}

void LS::LSDateController::setFromDate(QDate const& date)
{
    if(m_fromDate != date)
    {
        m_fromDate = date;
    }
}

QDate LS::LSDateController::getToDate() const
{
    return m_toDate;
}

void LS::LSDateController::setToDate(QDate const& date)
{
    if(m_toDate != date)
    {
        m_toDate = date;
    }
}

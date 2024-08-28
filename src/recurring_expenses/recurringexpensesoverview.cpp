#include "recurringexpensesoverview.h"

#include "recurringexpensemodel.h"
#include "ui_recurringexpensesoverview.h"

namespace LS = LambdaSnail::Juno::expenses;

LS::LSRecurringExpensesOverview::LSRecurringExpensesOverview(QWidget* parent, LSRecurringExpenseModel* recurringModel) :
    QWidget(parent),
    ui(new Ui::RecurringExpensesOverview),
    m_recurringModel(recurringModel)
{
    ui->setupUi(this);

    ui->recurringExpensesView->setModel(m_recurringModel);
    ui->recurringExpensesView->hideColumn(static_cast<int>(LSRecurringExpenseModel::Columns::id));
    ui->recurringExpensesView->hideColumn(static_cast<int>(LSRecurringExpenseModel::Columns::createdOn));
    ui->recurringExpensesView->hideColumn(static_cast<int>(LSRecurringExpenseModel::Columns::modifiedOn));
}

LS::LSRecurringExpensesOverview::~LSRecurringExpensesOverview() {
    delete ui;
}

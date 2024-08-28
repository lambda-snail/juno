// You may need to build the project (run Qt uic code generator) to get "ui_RecurringExpensesOverview.h" resolved

#include "LSRecurringExpensesOverview.h"
#include "ui_recurringexpensesoverview.h"

namespace LambdaSnail::Juno::expenses {
LSRecurringExpensesOverview::LSRecurringExpensesOverview(QWidget *parent) :
    QWidget(parent), ui(new Ui::RecurringExpensesOverview) {
    ui->setupUi(this);
}

LSRecurringExpensesOverview::~LSRecurringExpensesOverview() {
    delete ui;
}
} // LambdaSnail::Juno::expenses

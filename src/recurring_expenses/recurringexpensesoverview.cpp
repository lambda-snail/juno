// You may need to build the project (run Qt uic code generator) to get "ui_RecurringExpensesOverview.h" resolved

#include "recurringexpensesoverview.h"
#include "ui_recurringexpensesoverview.h"

namespace LambdaSnail::Juno::expenses {
RecurringExpensesOverview::RecurringExpensesOverview(QWidget *parent) :
    QWidget(parent), ui(new Ui::RecurringExpensesOverview) {
    ui->setupUi(this);
}

RecurringExpensesOverview::~RecurringExpensesOverview() {
    delete ui;
}
} // LambdaSnail::Juno::expenses

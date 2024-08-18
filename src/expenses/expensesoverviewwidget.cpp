//
// Created by niclas on 8/18/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExpensesOverviewWidget.h" resolved

#include "expensesoverviewwidget.h"
#include "ui_ExpensesOverviewWidget.h"

namespace LambdaSnail::Juno::expenses {
LSExpensesOverviewWidget::LSExpensesOverviewWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::ExpensesOverviewWidget) {
    ui->setupUi(this);
}

LSExpensesOverviewWidget::~LSExpensesOverviewWidget() {
    delete ui;
}
} // LambdaSnail::Juno::expenses

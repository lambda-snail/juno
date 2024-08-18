//
// Created by niclas on 8/18/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExpensesOverviewWidget.h" resolved

#include "expensemodel.h"
#include "expensesoverviewwidget.h"
#include "ui_ExpensesOverviewWidget.h"

namespace LambdaSnail::Juno::expenses
{
    LSExpensesOverviewWidget::LSExpensesOverviewWidget(QWidget *parent, LSExpenseModel* model) : QWidget(parent), ui(new Ui::ExpensesOverviewWidget), m_model(model)
    {
        ui->setupUi(this);

        ui->tableView->setModel(model);
    }

    LSExpensesOverviewWidget::~LSExpensesOverviewWidget()
    {
        delete ui;
    }
} // LambdaSnail::Juno::expenses

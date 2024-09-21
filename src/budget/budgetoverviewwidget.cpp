#include "budgetoverviewwidget.h"

namespace LambdaSnail::Juno::budget
{
    BudgetOverviewWidget::BudgetOverviewWidget(QWidget *parent) : QWidget(parent), ui(new Ui::BudgetOverviewWidget)
    {
        ui->setupUi(this);
    }
}

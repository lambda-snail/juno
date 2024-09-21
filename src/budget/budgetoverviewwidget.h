#pragma once

#include <ui_budgetoverviewwidget.h>

namespace LambdaSnail::Juno::budget
{
    class BudgetOverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit BudgetOverviewWidget(QWidget *parent = nullptr);

        ~BudgetOverviewWidget() override = default;

    private:
        std::unique_ptr<Ui::BudgetOverviewWidget> ui;
    };
}

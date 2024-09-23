#pragma once

#include <qdatawidgetmapper.h>
#include <ui_budgetoverviewwidget.h>

#include "budgetcategorybar.h"
#include "categories/categorymodel.h"
#include "expense_charts/aggregateexpensemodel.h"

namespace LambdaSnail::Juno::budget
{
    class LSBudgetOverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        void buildModelVisual();

        explicit LSBudgetOverviewWidget(categories::LSCategoryModel* categoryModel, expenses::LSAggregateExpenseModel* aggregateModel, QWidget *parent = nullptr);

        ~LSBudgetOverviewWidget() override = default;

    private:
        std::unique_ptr<Ui::BudgetOverviewWidget> ui;
        categories::LSCategoryModel* m_categoryModel;
        expenses::LSAggregateExpenseModel* m_aggregateModel;

        std::vector<std::unique_ptr<LSBudgetCategoryBar>> m_budgetCategories{};
    };
}

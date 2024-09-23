#pragma once

#include <qdatawidgetmapper.h>
#include <ui_budgetoverviewwidget.h>

#include "budgetcategorybar.h"
#include "categories/categorymodel.h"

namespace LambdaSnail::Juno::budget
{
    class LSBudgetOverviewWidget : public QWidget
    {
        Q_OBJECT

    public:
        void buildModelVisual();

        explicit LSBudgetOverviewWidget(categories::LSCategoryModel* categoryModel, QWidget *parent = nullptr);

        ~LSBudgetOverviewWidget() override = default;

    private:
        std::unique_ptr<Ui::BudgetOverviewWidget> ui;
        categories::LSCategoryModel* m_categoryModel;

        std::vector<std::unique_ptr<LSBudgetCategoryBar>> m_budgetCategories{};
    };
}

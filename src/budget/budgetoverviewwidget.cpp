#include "budgetoverviewwidget.h"

#include <QDataWidgetMapper>

#include "budgetcategorybar.h"

namespace LambdaSnail::Juno::budget
{
    void LSBudgetOverviewWidget::buildModelVisual()
    {
        if(not m_budgetCategories.empty())
        {
            m_budgetCategories.clear();
        }

        int32_t const numCategories = m_categoryModel->rowCount();
        for(int32_t c = 0; c < numCategories; ++c)
        {
            // TODO: Get current amount
            auto bar = std::make_unique<LSBudgetCategoryBar>(m_categoryModel,c, this);
            ui->formLayout->addRow(bar.get());
            m_budgetCategories.push_back(std::move(bar));
        }
    }

    LSBudgetOverviewWidget::LSBudgetOverviewWidget(categories::LSCategoryModel *categoryModel, QWidget *parent) : ui(new Ui::BudgetOverviewWidget), m_categoryModel(categoryModel)
    {
        ui->setupUi(this);
        buildModelVisual();
    }
}

#include "budgetoverviewwidget.h"

#include "budgetcategorybar.h"

namespace LambdaSnail::Juno::budget
{
    void LSBudgetOverviewWidget::buildModelVisual()
    {
        if(not m_budgetCategories.empty())
        {
            m_budgetCategories.clear();
        }

        int32_t numCategories = m_categoryModel->rowCount();
        int32_t categoryColumn = static_cast<int32_t>(categories::LSCategoryModel::Columns::category);
        int32_t limitColumn = static_cast<int32_t>(categories::LSCategoryModel::Columns::spending_limit);

        for(int32_t c = 0; c < numCategories; ++c)
        {
            QModelIndex category_i = m_categoryModel->index(c, categoryColumn);
            QModelIndex limit_i = m_categoryModel->index(c, limitColumn);

            QString const categoryName = m_categoryModel->data(category_i, Qt::DisplayRole).toString();
            double limit = m_categoryModel->data(limit_i, Qt::DisplayRole).toDouble();

            // TODO: Get current amount
            auto bar = std::make_unique<LSBudgetCategoryBar>(categoryName, 20, limit, this);
            m_budgetCategories.push_back(std::move(bar));
        }

        for(auto const& c : m_budgetCategories)
        {
            ui->formLayout->addRow(c.get());
        }
    }

    LSBudgetOverviewWidget::LSBudgetOverviewWidget(categories::LSCategoryModel *categoryModel, QWidget *parent) : ui(new Ui::BudgetOverviewWidget), m_categoryModel(categoryModel)
    {
        ui->setupUi(this);
        buildModelVisual();
    }
}

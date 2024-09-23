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
        for(int32_t category = 0; category < numCategories; ++category)
        {
            auto const total = m_aggregateModel->data(m_aggregateModel->index(category, 0), Qt::DisplayRole);
            auto bar = std::make_unique<LSBudgetCategoryBar>(m_categoryModel,category, this);
            bar->setCurrentAmount(total.toDouble());

            ui->formLayout->addRow(bar.get());
            m_budgetCategories.push_back(std::move(bar));
        }
    }

    LSBudgetOverviewWidget::LSBudgetOverviewWidget(categories::LSCategoryModel *categoryModel, expenses::LSAggregateExpenseModel* aggregateModel, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::BudgetOverviewWidget),
        m_categoryModel(categoryModel),
        m_aggregateModel(aggregateModel)
    {
        ui->setupUi(this);
        buildModelVisual();
    }
}

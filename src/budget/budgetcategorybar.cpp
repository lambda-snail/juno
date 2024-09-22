#include "budgetcategorybar.h"

namespace LambdaSnail::Juno::budget
{
    LSBudgetCategoryBar::LSBudgetCategoryBar(QStringView const &categoryName, double_t currentAmount, double_t limit, QWidget *parent)
        : m_limit(limit), m_currentAmount(currentAmount), m_categoryName(categoryName)
    {
        ui->setupUi(this);

        ui->categoryLimitVisual->setMinimum(0);
        connect(ui->categoryLimit, &QDoubleSpinBox::valueChanged, [this](double v)
        {
            this->setLimit(v);
        });
    }

    void LSBudgetCategoryBar::setCurrentAmount(double_t amount)
    {
        m_currentAmount = amount;
        ui->categoryLimitVisual->setValue(static_cast<int32_t>(m_currentAmount));
    }

    void LSBudgetCategoryBar::setLimit(double_t limit)
    {
        m_limit = limit;
        ui->categoryLimitVisual->setMaximum(static_cast<int32_t>(m_limit));
    }
}

#include "budgetcategorybar.h"

namespace LambdaSnail::Juno::budget
{
    LSBudgetCategoryBar::LSBudgetCategoryBar(QStringView const &categoryName, double_t currentAmount, double_t limit, QWidget *parent)
        :ui(new Ui::LSBudgetCategoryBar), m_limit(limit), m_currentAmount(currentAmount), m_categoryName(categoryName)
    {
        ui->setupUi(this);

        ui->categoryLabel->setText(categoryName.toString());
        updateValues();
        connect(ui->categoryLimit, &QDoubleSpinBox::valueChanged, [this](double v)
        {
            setLimit(v);
        });
    }

    void LSBudgetCategoryBar::setCurrentAmount(double_t amount)
    {
        m_currentAmount = amount;
        updateValues();
    }

    void LSBudgetCategoryBar::setLimit(double_t limit)
    {
        m_limit = limit;
        updateValues();
    }

    QAbstractSpinBox* LSBudgetCategoryBar::getLimitEditor() const
    {
        return ui->categoryLimit;
    }

    void LSBudgetCategoryBar::updateValues() const
    {
        ui->categoryLimitVisual->setMinimum(0);
        ui->categoryLimitVisual->setMaximum(static_cast<int32_t>(m_limit));
        ui->categoryLimitVisual->setValue(static_cast<int32_t>(m_currentAmount));
    }
}

#include "budgetcategorybar.h"

#include <QDataWidgetMapper>

namespace LambdaSnail::Juno::budget
{
    LSBudgetCategoryBar::LSBudgetCategoryBar(categories::LSCategoryModel* categoryModel, int32_t categoryIndex, QWidget *parent)
        : QWidget(parent), ui(new Ui::LSBudgetCategoryBar)
    {
        ui->setupUi(this);

        int32_t constexpr categoryColumn = static_cast<int32_t>(categories::LSCategoryModel::Columns::category);
        int32_t constexpr limitColumn = static_cast<int32_t>(categories::LSCategoryModel::Columns::spending_limit);

        QModelIndex category_i = categoryModel->index(categoryIndex, categoryColumn);
        QModelIndex limit_i = categoryModel->index(categoryIndex, limitColumn);

        m_categoryName = categoryModel->data(category_i, Qt::DisplayRole).toString();
        m_limit = categoryModel->data(limit_i, Qt::DisplayRole).toDouble();

        connect(ui->categoryLimit, &QDoubleSpinBox::valueChanged, [this](double v)
        {
            setLimit(v);
        });

        m_mapper = new QDataWidgetMapper(this);
        m_mapper->setModel(categoryModel);
        m_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
        m_mapper->addMapping(ui->categoryLimit, limitColumn);
        m_mapper->setCurrentIndex(categoryIndex);

        ui->categoryLabel->setText(m_categoryName);
        ui->categoryLabel->setFixedWidth(200);
    }

    void LSBudgetCategoryBar::setCurrentAmount(double_t amount)
    {
        m_currentAmount = amount;
        updateProgressBar();
    }

    void LSBudgetCategoryBar::setLimit(double_t limit)
    {
        m_limit = limit;
        updateProgressBar();
    }

    QAbstractSpinBox* LSBudgetCategoryBar::getLimitEditor() const
    {
        return ui->categoryLimit;
    }

    void LSBudgetCategoryBar::updateProgressBar() const
    {
        ui->categoryLimitVisual->setMinimum(0);
        ui->categoryLimitVisual->setMaximum(static_cast<int32_t>(m_limit));
        ui->categoryLimitVisual->setValue(static_cast<int32_t>(m_currentAmount));
    }
}

#pragma once

#include "ui_budgetcategorybar.h"

#include <QWidget>

namespace LambdaSnail::Juno::budget
{
    class LSBudgetCategoryBar : public QWidget
    {
        Q_OBJECT

        Q_PROPERTY(QStringView const& m_categoryName);
        Q_PROPERTY(double_t const& m_currentAmount WRITE setCurrentAmount);
        Q_PROPERTY(double_t const& m_limit WRITE setLimit);

    public:
        explicit LSBudgetCategoryBar(QStringView const& categoryName, double currentAmount, double limit, QWidget *parent = nullptr);

        ~LSBudgetCategoryBar() override = default;

        void setCurrentAmount(double_t amount);
        void setLimit(double_t limit);

    private:
        std::unique_ptr<Ui::LSBudgetCategoryBar> ui;

        double_t m_limit;
        double_t m_currentAmount;
        QStringView const& m_categoryName;
    };
}

#pragma once

#include <qdatawidgetmapper.h>

#include "ui_budgetcategorybar.h"

#include <QWidget>

#include "categories/categorymodel.h"

namespace LambdaSnail::Juno::budget
{
    class LSBudgetCategoryBar : public QWidget
    {
        Q_OBJECT

        Q_PROPERTY(QStringView const& m_categoryName);
        Q_PROPERTY(double_t const& m_currentAmount WRITE setCurrentAmount);
        Q_PROPERTY(double_t const& m_limit WRITE setLimit);

    public:
        explicit LSBudgetCategoryBar(categories::LSCategoryModel* categoryModel, int32_t categoryIndex, QWidget *parent = nullptr);

        ~LSBudgetCategoryBar() override = default;

        void setCurrentAmount(double_t amount);
        void setLimit(double_t limit);

        [[nodiscard]] QAbstractSpinBox* getLimitEditor() const;

    private:
        std::unique_ptr<Ui::LSBudgetCategoryBar> ui;
        QDataWidgetMapper* m_mapper;

        double_t m_limit{};
        double_t m_currentAmount{};
        QString m_categoryName{};

        void updateProgressBar() const;
    };
}

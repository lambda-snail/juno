#pragma once

#include <QDate>
#include <QObject>

namespace LambdaSnail::Juno::expenses
{
    class LSExpenseModel;
}

namespace LambdaSnail::Juno::shared
{
    class LSDateController : QObject
    {
        Q_OBJECT

        Q_PROPERTY(QDate m_fromDate READ getFromDate WRITE setFromDate)
        Q_PROPERTY(QDate m_toDate READ getToDate WRITE setToDate)

    public:
        explicit LSDateController(expenses::LSExpenseModel& model, QObject* parent = nullptr);

        void updateDateLimits() const;

        [[nodiscard]] QDate getFromDate() const;
        void setFromDate(QDate const& date);

        [[nodiscard]] QDate getToDate() const;
        void setToDate(QDate const& date);

    private:
        QDate m_fromDate{};
        QDate m_toDate{};

        expenses::LSExpenseModel& m_model;
    };
}

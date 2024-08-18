#pragma once

#include <QWidget>

namespace LambdaSnail::Juno::expenses {
QT_BEGIN_NAMESPACE
namespace Ui { class ExpensesOverviewWidget; }
QT_END_NAMESPACE

class LSExpensesOverviewWidget : public QWidget {
Q_OBJECT

public:
    explicit LSExpensesOverviewWidget(QWidget *parent = nullptr);
    ~LSExpensesOverviewWidget() override;

private:
    Ui::ExpensesOverviewWidget *ui;
};
} // LambdaSnail::Juno::expenses

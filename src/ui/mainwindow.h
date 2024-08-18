#pragma once


#include <QMainWindow>

#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno {

    namespace expenses
    {
        class LSExpensesOverviewWidget;
    }

    QT_BEGIN_NAMESPACE
namespace Ui { class LSMainWindow; }
QT_END_NAMESPACE

class LSMainWindow : public QMainWindow {
Q_OBJECT

public:
void setUpToolMenu();

    explicit LSMainWindow(expenses::LSExpenseModel* expenseModel);
    ~LSMainWindow() override;

private:
    Ui::LSMainWindow *ui;

    expenses::LSExpenseModel* m_expenseModel;
    expenses::LSExpensesOverviewWidget* expensesOverview;
};
}


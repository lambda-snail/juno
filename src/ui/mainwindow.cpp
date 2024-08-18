#include "mainwindow.h"
#include "../../cmake-build-debug/cmake-build-debug/juno_autogen/include/ui_mainwindow.h"

#include "expenses/expensesoverviewwidget.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setUpToolMenu()
    {
        // Filer dates set to current year for convenience
        int const currentYear = QDate::currentDate().year();
        ui->fromDate->setDate(QDate(currentYear, 1, 1));
        ui->toDate->setDate(QDate(currentYear, 12, 31));
    }

    LSMainWindow::LSMainWindow(expenses::LSExpenseModel* expenseModel) :
        QMainWindow(nullptr),
        ui(new Ui::LSMainWindow),
        m_expenseModel(expenseModel)
    {
        setWindowTitle("Juno Expense Tracker");

        ui->setupUi(this);
        setUpToolMenu();

        expensesOverviewWidget = new expenses::LSExpensesOverviewWidget(this, expenseModel);
        ui->mdiArea->addSubWindow(expensesOverviewWidget);
    }

    LSMainWindow::~LSMainWindow()
    {
        delete ui;
    }
}

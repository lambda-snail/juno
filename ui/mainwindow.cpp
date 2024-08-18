#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableView>
#include <QListWidget>

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

        QTableView* expensesTableView = new QTableView(this);
        expensesTableView->setModel(expenseModel);
        ui->mdiArea->addSubWindow(expensesTableView);

        expenses::LSExpenseModel* m = new expenses::LSExpenseModel();
    }

    LSMainWindow::~LSMainWindow()
    {
        delete ui;
    }
}

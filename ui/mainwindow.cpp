#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
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

    LSMainWindow::LSMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LSMainWindow)
    {
        setWindowTitle("Juno Expense Tracker");

        ui->setupUi(this);
        setUpToolMenu();
    }

    LSMainWindow::~LSMainWindow()
    {
        delete ui;
    }
}

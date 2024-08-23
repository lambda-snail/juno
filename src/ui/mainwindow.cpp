#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "expenses/expensesoverviewwidget.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setupMenu()
    {
        connect(ui->expensesButton, &QPushButton::pressed, this, &LSMainWindow::onExpenseMenuClicked);
        connect(ui->chartsButton, &QPushButton::pressed, this, &LSMainWindow::onChartsMenuClicked);


        m_expensesIndex = ui->widgetStack->addWidget(expensesOverviewWidget);
        m_chartsIndex = ui->widgetStack->addWidget(chartsWidget);
    }

    LSMainWindow::LSMainWindow(expenses::LSExpenseModel* expenseModel) :
        QMainWindow(nullptr),
        ui(new Ui::LSMainWindow),
        m_expenseModel(expenseModel)
    {
        setWindowTitle("Juno Expense Tracker");

        ui->setupUi(this);

        expensesOverviewWidget = new expenses::LSExpensesOverviewWidget(ui->widgetStack, expenseModel);
        chartsWidget = new QWidget(this);

        setupMenu();

        //ui->mdiArea->addSubWindow(expensesOverviewWidget);
    }

    LSMainWindow::~LSMainWindow()
    {
        delete ui;
    }

    void LSMainWindow::onExpenseMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_expensesIndex);
    }

    void LSMainWindow::onChartsMenuClicked()
    {
        ui->widgetStack->setCurrentIndex(m_chartsIndex);
    }
}

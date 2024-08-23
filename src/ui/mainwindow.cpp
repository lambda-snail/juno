#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../external/QtAwesome/QtAwesome/QtAwesome.h"

#include "expenses/expensesoverviewwidget.h"

namespace LambdaSnail::Juno
{
    void LSMainWindow::setupMenu()
    {
        ui->expensesButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_balance_scale));
        ui->chartsButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_area_chart));

        connect(ui->expensesButton, &QPushButton::pressed, this, &LSMainWindow::onExpenseMenuClicked);
        connect(ui->chartsButton, &QPushButton::pressed, this, &LSMainWindow::onChartsMenuClicked);

        m_expensesIndex = ui->widgetStack->addWidget(expensesOverviewWidget);
        m_chartsIndex = ui->widgetStack->addWidget(chartsWidget);
    }

    LSMainWindow::LSMainWindow(expenses::LSExpenseModel* expenseModel, fa::QtAwesome* qtAwesome) :
        QMainWindow(nullptr),
        m_qtAwesome(qtAwesome),
        ui(new Ui::LSMainWindow),
        m_expenseModel(expenseModel)
    {
        setWindowTitle("Juno Expense Tracker");

        ui->setupUi(this);

        expensesOverviewWidget = new expenses::LSExpensesOverviewWidget(ui->widgetStack, expenseModel, qtAwesome);
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

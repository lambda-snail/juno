//
// Created by niclas on 8/18/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ExpensesOverviewWidget.h" resolved

#include "expensemodel.h"
#include "expensesoverviewwidget.h"

#include <QDateEdit>

#include "ui_ExpensesOverviewWidget.h"

namespace LambdaSnail::Juno::expenses
{
    void LSExpensesOverviewWidget::setUpToolbar()
    {
        ui->toolBar->addSeparator();

        auto* fromDate = new QDateEdit(this);
        auto* toDate = new QDateEdit(this);

        fromDate->setDisplayFormat("yyyy-MM-dd"); // TODO: Store date format in settings
        toDate->setDisplayFormat("yyyy-MM-dd");

        fromDate->setCalendarPopup(true);
        toDate->setCalendarPopup(true);

        // Filer dates set to current year for convenience
        int const currentYear = QDate::currentDate().year();
        fromDate->setDate(QDate(currentYear, 1, 1));
        toDate->setDate(QDate(currentYear, 12, 31));

        ui->toolBar->addWidget(fromDate);
        ui->toolBar->addWidget(toDate);
    }

    LSExpensesOverviewWidget::LSExpensesOverviewWidget(QWidget *parent, LSExpenseModel* model) : QWidget(parent), ui(new Ui::ExpensesOverviewWidget), m_model(model)
    {
        ui->setupUi(this);

        ui->tableView->setModel(model);

        setUpToolbar();
    }

    LSExpensesOverviewWidget::~LSExpensesOverviewWidget()
    {
        delete ui;
    }
} // LambdaSnail::Juno::expenses

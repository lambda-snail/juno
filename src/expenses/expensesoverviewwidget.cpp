#include "expensemodel.h"
#include "expensesoverviewwidget.h"

#include <QDateEdit>
#include <QPushButton>
#include <QSqlError>

#include "QtAwesome.h"
#include "ui_expensesoverviewwidget.h"

namespace LambdaSnail::Juno::expenses
{
    void LSExpensesOverviewWidget::setUpToolbar(fa::QtAwesome* qtAwesome)
    {
        searchButton = new QPushButton();
        searchButton->setText("Search");
        searchButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_magnifying_glass));

        ui->toolBar->addWidget(searchButton);

        ui->toolBar->addSeparator();

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

        // TODO: Add signals and slots to listen to date change
        connect(fromDate, &QDateEdit::dateChanged, this, &LSExpensesOverviewWidget::onSearchDatesChanged);
    }

    LSExpensesOverviewWidget::LSExpensesOverviewWidget(QWidget *parent, LSExpenseModel* model, fa::QtAwesome* qtAwesome) : QWidget(parent), ui(new Ui::ExpensesOverviewWidget), m_model(model)
    {
        ui->setupUi(this);

        fromDate = new QDateEdit(this);
        toDate = new QDateEdit(this);

        setUpToolbar(qtAwesome);

        ui->tableView->setModel(model);
    }

    LSExpensesOverviewWidget::~LSExpensesOverviewWidget()
    {
        delete ui;
    }

    void LSExpensesOverviewWidget::onSearchDatesChanged()
    {
        m_model->setDateFilter(fromDate->date(), toDate->date());
    }
}

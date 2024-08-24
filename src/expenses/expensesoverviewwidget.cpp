#include "expensemodel.h"
#include "expensesoverviewwidget.h"
#include "datefromstringdelegate.h"

#include <QDateEdit>
#include <QPushButton>
#include <QSqlError>

#include "QtAwesome.h"
#include "ui_expensesoverviewwidget.h"
#include "shared/database_manager.h"


namespace LambdaSnail::Juno::expenses
{
    void LSExpensesOverviewWidget::setUpToolbar(fa::QtAwesome* qtAwesome)
    {
        // Search button
        searchButton = new QPushButton(this);
        searchButton->setText("Search");
        searchButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_magnifying_glass));

        // Date selectors
        fromDate->setDisplayFormat("yyyy-MM-dd"); // TODO: Store date format in settings
        toDate->setDisplayFormat("yyyy-MM-dd");

        fromDate->setCalendarPopup(true);
        toDate->setCalendarPopup(true);

        // Filer dates set to current year for convenience
        int const currentYear = QDate::currentDate().year();
        fromDate->setDate(QDate(currentYear, 1, 1));
        toDate->setDate(QDate(currentYear, 12, 31));

        // New Expense
        QPushButton* newExpense = new QPushButton(this);
        newExpense->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_square_plus));

        // Build the toolbar
        ui->toolBar->addWidget(fromDate);
        ui->toolBar->addWidget(toDate);
        ui->toolBar->addWidget(searchButton);
        ui->toolBar->addSeparator();
        ui->toolBar->addWidget(newExpense);

        // TODO: Add signals and slots to listen to date change
        connect(fromDate, &QDateEdit::dateChanged, this, &LSExpensesOverviewWidget::onSearchDatesChanged);
        connect(newExpense, &QPushButton::pressed, this, [&]()
        {
            m_model->insertRow(0);
        });
    }

    LSExpensesOverviewWidget::LSExpensesOverviewWidget(QWidget *parent, LSExpenseModel* model, fa::QtAwesome* qtAwesome) : QWidget(parent), ui(new Ui::ExpensesOverviewWidget), m_model(model)
    {
        ui->setupUi(this);

        fromDate = new QDateEdit(this);
        toDate = new QDateEdit(this);

        setUpToolbar(qtAwesome);

        using ExpenseColumns = shared::LSDatabaseManager::ExpenseColumns;

        // TODO: Listen to column size changes and store somewhere for persistence between sessions
        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::id), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::createdOn), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::modifiedOn), true);
        ui->tableView->setSortingEnabled(true);

        m_dateColumnDelegate = std::make_unique<DateFromStringDelegate>();
        ui->tableView->setItemDelegateForColumn(static_cast<int32_t>(ExpenseColumns::date), m_dateColumnDelegate.get());

        onSearchDatesChanged();
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

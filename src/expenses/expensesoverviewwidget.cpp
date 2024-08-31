#include "expensemodel.h"
#include "expensesoverviewwidget.h"
#include "datefromstringdelegate.h"

#include <QDateEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSqlError>

#include "QtAwesome.h"
#include "ui_expensesoverviewwidget.h"
#include "shared/database_manager.h"


namespace LambdaSnail::Juno::expenses
{
    LSExpensesOverviewWidget::LSExpensesOverviewWidget(QWidget *parent, QStatusBar* statusBar, LSExpenseModel* model, fa::QtAwesome *qtAwesome) :
        QWidget(parent),
        m_statusBar(statusBar),
        ui(new Ui::ExpensesOverviewWidget),
        m_model(model)
    {
        ui->setupUi(this);

        setUpToolbar(qtAwesome);
        setupTableView(model);
    }

    void LSExpensesOverviewWidget::setUpToolbar(fa::QtAwesome *qtAwesome)
    {
        // Search button
        // m_searchButton = new QPushButton(this);
        // m_searchButton->setText("Search");
        // m_searchButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_magnifying_glass));

        // New Expense
        m_newExpenseButton = new QPushButton(this);
        m_newExpenseButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_square_plus));

        // Delete Expense
        m_deleteExpenseButton = new QPushButton(this);
        m_deleteExpenseButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_trash_can));
        m_deleteExpenseButton->setEnabled(false);

        // Build the toolbar
        //ui->toolBar->addWidget(m_searchButton);
        //ui->toolBar->addSeparator();
        ui->toolBar->addWidget(m_newExpenseButton);
        ui->toolBar->addWidget(m_deleteExpenseButton);

        //connect(m_fromDate, &QDateEdit::dateChanged, this, &LSExpensesOverviewWidget::onSearchDatesChanged);

        connect(m_newExpenseButton, &QPushButton::pressed, this, [&]()
        {
            m_model->insertRow(0);
        });

        connect(m_deleteExpenseButton, &QPushButton::pressed, this, [&]()
        {
            QItemSelection const selection = ui->tableView->selectionModel()->selection();
            for(auto const& range : selection)
            //for(auto const& range : selection->mapSelectionToSource(selection)) // When using proxy model
            {
                m_model->removeRows(range.top(), range.height());
                for(auto const& row : range.indexes())
                {
                    ui->tableView->hideRow(row.row());
                }
            }

            m_model->submitAll();
            m_statusBar->showMessage(tr("Expenses deleted!"), 4000);
        });
    }


    void LSExpensesOverviewWidget::setupTableView(LSExpenseModel* model)
    {
        using ExpenseColumns = LSExpenseModel::Columns;

        // TODO: Listen to column size changes and store somewhere for persistence between sessions
        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::id), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::relatedExpense), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::createdOn), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::modifiedOn), true);
        ui->tableView->setSortingEnabled(true);

        m_dateColumnDelegate = std::make_unique<LSDateFromStringDelegate>();
        ui->tableView->setItemDelegateForColumn(static_cast<int32_t>(ExpenseColumns::date), m_dateColumnDelegate.get());

        m_model->select();

        connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
                &LSExpensesOverviewWidget::onSelectionChanged);

    }

    LSExpensesOverviewWidget::~LSExpensesOverviewWidget()
    {
        delete ui;
    }

    void LSExpensesOverviewWidget::onSelectionChanged(/*QItemSelection const &selected, QItemSelection const &deselected*/)
    {
        m_deleteExpenseButton->setEnabled(ui->tableView->selectionModel()->hasSelection());
    }
}

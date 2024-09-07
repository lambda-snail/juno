#include "expensesoverviewwidget.h"
#include "ui_expensesoverviewwidget.h"

#include "QtAwesome.h"

#include "categoryfiltermodel.h"
#include "expensemodel.h"
#include "categories/categorymodel.h"
#include "shared/date_time/datefromstringdelegate.h"

namespace LambdaSnail::Juno::expenses
{
    LSExpensesOverviewWidget::LSExpensesOverviewWidget(
        QWidget *parent,
        QStatusBar *statusBar,
        QAbstractProxyModel *expenseModel,
        QAbstractProxyModel *categoryModel,
        QSettings *settings,
        fa::QtAwesome *qtAwesome) :
            QWidget(parent),
            ui(new Ui::ExpensesOverviewWidget),
            m_expenseModel(expenseModel),
            m_categoryModel(categoryModel),
            m_statusBar(statusBar),
            m_settings(settings)
    {
        ui->setupUi(this);

        setUpToolbar(qtAwesome);
        setupTableView(expenseModel);
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

        // Category Filter

        QComboBox *categoryList = new QComboBox(this);
        categoryList->setModel(m_categoryModel);
        categoryList->setModelColumn(static_cast<int>(categories::LSCategoryModel::Columns::category));
        categoryList->setEditable(false);

        QPushButton *clearFilterButton = new QPushButton(this);
        clearFilterButton->setIcon(qtAwesome->icon(fa::fa_solid, fa::fa_filter_circle_xmark));

        // Build the toolbar
        //ui->toolBar->addWidget(m_searchButton);
        //ui->toolBar->addSeparator();
        ui->toolBar->addWidget(m_newExpenseButton);
        ui->toolBar->addWidget(m_deleteExpenseButton);
        ui->toolBar->addSeparator();
        ui->toolBar->addWidget(categoryList);
        ui->toolBar->addWidget(clearFilterButton);

        //connect(m_fromDate, &QDateEdit::dateChanged, this, &LSExpensesOverviewWidget::onSearchDatesChanged);

        connect(m_newExpenseButton, &QPushButton::pressed, this, [&]()
        {
            m_expenseModel->insertRow(0);
        });

        connect(m_deleteExpenseButton, &QPushButton::pressed, this, [&]()
        {
            QItemSelection const selection = ui->tableView->selectionModel()->selection();
            for (auto const &range: selection)
            {
                m_expenseModel->removeRows(range.top(), range.height());
                for (auto const &row: range.indexes())
                {
                    ui->tableView->hideRow(row.row());
                }
            }

            m_expenseModel->sourceModel()->submit();
            m_statusBar->showMessage(tr("Expenses deleted!"), 4000);
        });

        connect(categoryList, &QComboBox::currentTextChanged, this, [&](QString const &text)
        {
            // Ugly but works for now
            auto *filter = qobject_cast<LSCategoryFilterModel*>(m_expenseModel);
            filter->setFilterCategory(text);
        });

        connect(clearFilterButton, &QPushButton::pressed, this, [&]()
        {
            // TODO: Find a neat way to avoid these casts
            auto *filter = qobject_cast<LSCategoryFilterModel*>(m_expenseModel);
            filter->setInactive();
        });
    }

    void LSExpensesOverviewWidget::setupTableView(QAbstractProxyModel *model)
    {
        using ExpenseColumns = LSExpenseModel::Columns;

        // TODO: Listen to column size changes and store somewhere for persistence between sessions
        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::id), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::relatedExpense), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::createdOn), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::modifiedOn), true);
        ui->tableView->setSortingEnabled(true);

        m_dateColumnDelegate = std::make_unique<shared::LSDateFromStringDelegate>(m_settings);
        ui->tableView->setItemDelegateForColumn(static_cast<int32_t>(ExpenseColumns::date), m_dateColumnDelegate.get());

        ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

        connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
                &LSExpensesOverviewWidget::onSelectionChanged);
    }

    LSExpensesOverviewWidget::~LSExpensesOverviewWidget()
    {
        delete ui;
    }

    void LSExpensesOverviewWidget::onSelectionChanged(
        /*QItemSelection const &selected, QItemSelection const &deselected*/)
    {
        m_deleteExpenseButton->setEnabled(ui->tableView->selectionModel()->hasSelection());
    }
}

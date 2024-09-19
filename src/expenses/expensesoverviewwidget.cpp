#include "expensesoverviewwidget.h"
#include "ui_expensesoverviewwidget.h"

#include "QtAwesome.h"

#include "categoryfiltermodel.h"
#include "expensemodel.h"
#include "expensetoolbarfactory.h"
#include "categories/categorymodel.h"
#include "shared/date_time/datefromstringdelegate.h"
#include "shared/delegates/relationalproxydelegate.h"

namespace LambdaSnail::Juno::expenses
{
    LSExpensesOverviewWidget::LSExpensesOverviewWidget(
        QWidget *parent,
        QStatusBar *statusBar,
        LSExpenseModel *expenseModel,
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
        setupTableView();
        m_toolBarItems = LSExpenseToolBarFactory::setUpToolbar(this, m_categoryFilterModel, m_categoryModel, static_cast<int>(categories::LSCategoryModel::Columns::category), ui->tableView, ui->toolBar, qtAwesome);
    }

    void LSExpensesOverviewWidget::setupTableView()
    {
        using ExpenseColumns = LSExpenseModel::Columns;

        m_categoryFilterModel = new LSCategoryFilterModel(this, static_cast<int>(LSExpenseModel::Columns::category));
        m_categoryFilterModel->setSourceModel(m_expenseModel);

        // TODO: Listen to column size changes and store somewhere for persistence between sessions
        ui->tableView->setModel(m_categoryFilterModel);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::id), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::relatedExpense), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::createdOn), true);
        ui->tableView->setColumnHidden(static_cast<int>(ExpenseColumns::modifiedOn), true);
        ui->tableView->setSortingEnabled(true);

        ui->tableView->verticalHeader()->setVisible(false);

        m_dateColumnDelegate = std::make_unique<shared::LSDateFromStringDelegate>(m_settings);
        ui->tableView->setItemDelegateForColumn(static_cast<int32_t>(ExpenseColumns::date), m_dateColumnDelegate.get());

        m_categoryColumnDelegate = std::make_unique<delegates::LSRelationalProxyDelegate>(ui->tableView);
        ui->tableView->setItemDelegate(m_categoryColumnDelegate.get());
    }

    LSExpensesOverviewWidget::~LSExpensesOverviewWidget()
    {
        delete ui;
    }

    void LSExpensesOverviewWidget::onSelectionChanged() const
    {
        //m_deleteExpenseButton->setEnabled(ui->tableView->selectionModel()->hasSelection());
        m_toolBarItems->DeleteExpenseButton->setEnabled(ui->tableView->selectionModel()->hasSelection());
    }
}

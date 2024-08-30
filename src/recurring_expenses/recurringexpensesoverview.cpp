#include "recurringexpensesoverview.h"

#include <qabstractproxymodel.h>

#include "ui_recurringexpensesoverview.h"
#include "recurringexpensemodel.h"

#include <QDataWidgetMapper>

#include "relatedexpenseproxymodel.h"
#include "expenses/expensemodel.h"

namespace LS = LambdaSnail::Juno::expenses;

void LambdaSnail::Juno::expenses::LSRecurringExpensesOverview::setUpMapper()
{
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_recurringModel);

    m_mapper->setSubmitPolicy(QDataWidgetMapper::SubmitPolicy::AutoSubmit);

    m_mapper->addMapping(ui->recipientLineEdit, static_cast<int>(LSRecurringExpenseModel::Columns::recipient));
    m_mapper->addMapping(ui->amountDoubleSpinBox, static_cast<int>(LSRecurringExpenseModel::Columns::amount));
    m_mapper->addMapping(ui->activeFromDateEdit, static_cast<int>(LSRecurringExpenseModel::Columns::activeFrom));
    m_mapper->addMapping(ui->activeToDateEdit, static_cast<int>(LSRecurringExpenseModel::Columns::activeTo));

    m_mapper->addMapping(ui->billingDaySpinBox, static_cast<int>(LSRecurringExpenseModel::Columns::billingDay));
    m_mapper->addMapping(ui->descriptionLineEdit, static_cast<int>(LSRecurringExpenseModel::Columns::description));
    m_mapper->addMapping(ui->categoryLineEdit, static_cast<int>(LSRecurringExpenseModel::Columns::category));
}

void LambdaSnail::Juno::expenses::LSRecurringExpensesOverview::setUpRecurringExpensesView()
{
    ui->recurringExpensesView->setModel(m_recurringModel);
    ui->recurringExpensesView->setModelColumn(static_cast<int>(LSRecurringExpenseModel::Columns::recipient));

    connect(ui->recurringExpensesView, &QListView::clicked, [&](QModelIndex const& index)
    {
        m_mapper->setCurrentIndex(index.row());
    });
}

void LambdaSnail::Juno::expenses::LSRecurringExpensesOverview::setUpRelatedExpensesView()
{
    ui->relatedExpensesView->setModel(m_expensesProxyModel);
    ui->relatedExpensesView->setColumnHidden(static_cast<int>(LSExpenseModel::Columns::id), true);
    ui->relatedExpensesView->setColumnHidden(static_cast<int>(LSExpenseModel::Columns::relatedExpense), true);
    ui->relatedExpensesView->setColumnHidden(static_cast<int>(LSExpenseModel::Columns::createdOn), true);
    ui->relatedExpensesView->setColumnHidden(static_cast<int>(LSExpenseModel::Columns::modifiedOn), true);
    ui->relatedExpensesView->setSortingEnabled(true);

    connect(ui->recurringExpensesView, &QListView::clicked, [&](QModelIndex const& index)
    {
        // TODO: Use proxy model and ->mapToSource(index); ?
        QModelIndex sourceIndex = m_recurringModel->mapToSource(index);
        int32_t rowId = m_recurringModel->data(sourceIndex, static_cast<int>(LSRecurringExpenseModel::Roles::IdRole)).toInt();
        m_expensesProxyModel->setRelatedExpense(rowId);
    });
}

LS::LSRecurringExpensesOverview::LSRecurringExpensesOverview(QWidget* parent, LSRelatedExpenseProxyModel* expensesProxyModel, QAbstractProxyModel* recurringModel) :
    QWidget(parent),
    ui(new Ui::RecurringExpensesOverview),
    m_recurringModel(recurringModel),
    m_expensesProxyModel(expensesProxyModel)
{
    ui->setupUi(this);

    setUpMapper();
    setUpRecurringExpensesView();
    setUpRelatedExpensesView();
}

LS::LSRecurringExpensesOverview::~LSRecurringExpensesOverview() {
    delete ui;
}

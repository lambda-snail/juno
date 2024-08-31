#include "recurringexpensesoverview.h"

#include <qabstractproxymodel.h>

#include "ui_recurringexpensesoverview.h"
#include "recurringexpensemodel.h"

#include <QDataWidgetMapper>

#include "QtAwesome.h"
#include "relatedexpenseproxymodel.h"
#include "expenses/datefromstringdelegate.h"
#include "expenses/expensemodel.h"
#include "shared/datecontroller.h"

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

    m_dateColumnDelegate = std::make_unique<LSDateFromStringDelegate>();
    ui->relatedExpensesView->setItemDelegateForColumn(static_cast<int32_t>(LSExpenseModel::Columns::date), m_dateColumnDelegate.get());

    connect(ui->recurringExpensesView, &QListView::clicked, [&](QModelIndex const& index)
    {
        QModelIndex sourceIndex = m_recurringModel->mapToSource(index);
        int32_t rowId = m_recurringModel->data(sourceIndex, static_cast<int>(LSRecurringExpenseModel::Roles::IdRole)).toInt();
        m_expensesProxyModel->setRelatedExpense(rowId);

        ui->newExpenseButton->setEnabled(true);
    });

    ui->newExpenseButton->setEnabled(false);
    ui->newExpenseButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_square_plus));
    connect(ui->newExpenseButton, &QPushButton::pressed, this, [&]()
    {
        int32_t newModelIndex = 0;

        m_expensesProxyModel->setDynamicSortFilter(false);

        m_expensesProxyModel->insertRow(newModelIndex);

        auto setValue = [&](int32_t viewIndex, LSExpenseModel::Columns column, auto value)
        {
            QModelIndex index = m_expensesProxyModel->index(viewIndex, static_cast<int>(column));
            m_expensesProxyModel->setData(index, value);
        };

        setValue(newModelIndex, LSExpenseModel::Columns::recipient, ui->recipientLineEdit->text());
        setValue(newModelIndex, LSExpenseModel::Columns::category, ui->categoryLineEdit->text());
        setValue(newModelIndex, LSExpenseModel::Columns::amount, ui->amountDoubleSpinBox->value());

        QModelIndex currentRecurringExpenseIndex = m_recurringModel->mapToSource( ui->recurringExpensesView->currentIndex() );
        int32_t recurringExpenseId = m_recurringModel->data(currentRecurringExpenseIndex, static_cast<int>(LSRecurringExpenseModel::Roles::IdRole)).toInt();
        setValue(newModelIndex, LSExpenseModel::Columns::relatedExpense, recurringExpenseId);

        // Suggest a date based on the global from date, the current month and the given billing day
        QDate now = QDate::currentDate();
        QDate suggestedDate(m_dateController->getFromDate().year(), now.month(), ui->billingDaySpinBox->value());
        setValue(newModelIndex, LSExpenseModel::Columns::date, suggestedDate);

        m_expensesProxyModel->submit();

        m_expensesProxyModel->setDynamicSortFilter(true);
    });
}

LS::LSRecurringExpensesOverview::LSRecurringExpensesOverview(QWidget* parent, LSRelatedExpenseProxyModel* expensesProxyModel, QAbstractProxyModel* recurringModel, shared::LSDateController* dateController, fa::QtAwesome* qtAwesome) :
    QWidget(parent),
    ui(new Ui::RecurringExpensesOverview),
    m_dateController(dateController),
    m_recurringModel(recurringModel),
    m_expensesProxyModel(expensesProxyModel),
    m_qtAwesome(qtAwesome)
{
    ui->setupUi(this);

    setUpMapper();
    setUpRecurringExpensesView();
    setUpRelatedExpensesView();
}

LS::LSRecurringExpensesOverview::~LSRecurringExpensesOverview() {
    delete ui;
}

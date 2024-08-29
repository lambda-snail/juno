#include "recurringexpensesoverview.h"
#include "ui_recurringexpensesoverview.h"
#include "recurringexpensemodel.h"

#include <QDataWidgetMapper>

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

LS::LSRecurringExpensesOverview::LSRecurringExpensesOverview(QWidget* parent, LSRecurringExpenseModel* recurringModel) :
    QWidget(parent),
    ui(new Ui::RecurringExpensesOverview),
    m_recurringModel(recurringModel)
{
    ui->setupUi(this);

    setUpMapper();

    ui->recurringExpensesView->setModel(m_recurringModel);
    ui->recurringExpensesView->setModelColumn(static_cast<int>(LSRecurringExpenseModel::Columns::recipient));

    connect(ui->recurringExpensesView, &QListView::clicked, [&](QModelIndex const& index)
    {
        m_mapper->setCurrentIndex(index.row());
    });
}

LS::LSRecurringExpensesOverview::~LSRecurringExpensesOverview() {
    delete ui;
}

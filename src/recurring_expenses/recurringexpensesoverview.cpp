#include "recurringexpensesoverview.h"
#include "ui_recurringexpensesoverview.h"

#include <qabstractproxymodel.h>

#include "recurringexpensemodel.h"

#include <QDataWidgetMapper>
#include <QLineEdit>
#include <QSqlRelationalDelegate>

#include "QtAwesome.h"
#include "relatedexpenseproxymodel.h"
#include "categories/categorymodel.h"
#include "shared/date_time/datefromstringdelegate.h"
#include "expenses/expensemodel.h"
#include "expenses/expensetoolbarfactory.h"
#include "shared/applicationcontext.h"
#include "shared/datecontroller.h"
#include "shared/date_time/datetimehelpers.h"
#include "shared/delegates/relationalproxydelegate.h"

namespace LS = LambdaSnail::Juno::expenses;

void LambdaSnail::Juno::expenses::LSRecurringExpensesOverview::setUpMapper()
{
    m_mapper = new QDataWidgetMapper(this);
    m_mapper->setModel(m_recurringModel);

    m_mapper->setSubmitPolicy(QDataWidgetMapper::SubmitPolicy::ManualSubmit);

    m_mapper->addMapping(ui->recipientLineEdit, static_cast<int>(LSRecurringExpenseModel::Columns::recipient));
    m_mapper->addMapping(ui->amountDoubleSpinBox, static_cast<int>(LSRecurringExpenseModel::Columns::amount));
    m_mapper->addMapping(ui->activeFromDateEdit, static_cast<int>(LSRecurringExpenseModel::Columns::activeFrom));
    m_mapper->addMapping(ui->activeToDateEdit, static_cast<int>(LSRecurringExpenseModel::Columns::activeTo));

    m_mapper->addMapping(ui->billingDaySpinBox, static_cast<int>(LSRecurringExpenseModel::Columns::billingDay));
    m_mapper->addMapping(ui->descriptionLineEdit, static_cast<int>(LSRecurringExpenseModel::Columns::description));

    m_mapper->addMapping(ui->categoryComboBox, static_cast<int>(LSRecurringExpenseModel::Columns::category));
    m_mapperDelegate = std::make_unique<delegates::LSRelationalProxyDelegate>(this);
    m_mapper->setItemDelegate(m_mapperDelegate.get());
}

void LambdaSnail::Juno::expenses::LSRecurringExpensesOverview::setUpRecurringExpensesView()
{
    ui->recurringExpensesView->setModel(m_recurringModel);
    ui->recurringExpensesView->setModelColumn(static_cast<int>(LSRecurringExpenseModel::Columns::recipient));

    ui->activeFromDateEdit->setCalendarPopup(true);
    ui->activeToDateEdit->setCalendarPopup(true);

    connect(ui->recurringExpensesView, &QTableView::clicked, [&](QModelIndex const& index)
    {
        ui->submitChangesButton->setEnabled(true);
        m_mapper->setCurrentIndex(index.row());
    });

    ui->submitChangesButton->setEnabled(false);
    connect(ui->submitChangesButton, &QPushButton::clicked, this, [&]()
    {
        m_mapper->submit();
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
    ui->relatedExpensesView->sortByColumn(static_cast<int>(LSRecurringExpenseModel::Columns::recipient), Qt::SortOrder::AscendingOrder);

    m_dateColumnDelegate = std::make_unique<shared::LSDateFromStringDelegate>(m_settings);
    ui->relatedExpensesView->setItemDelegateForColumn(static_cast<int32_t>(LSExpenseModel::Columns::date), m_dateColumnDelegate.get());

    m_categoryColumnDelegate = std::make_unique<delegates::LSRelationalProxyDelegate>(ui->relatedExpensesView);
    ui->relatedExpensesView->setItemDelegateForColumn(static_cast<int32_t>(LSExpenseModel::Columns::category), m_categoryColumnDelegate.get());

    connect(ui->recurringExpensesView, &QTableView::clicked, [&](QModelIndex const& index)
    {
        // index is an index into the model, not the view
        int32_t rowId = m_recurringModel->data(index, static_cast<int>(LSRecurringExpenseModel::Roles::IdRole)).toInt();
        m_expensesProxyModel->setRelatedExpense(rowId);
        ui->newExpenseButton->setEnabled(true);
    });

    ui->newExpenseButton->setEnabled(false);
    ui->newExpenseButton->setIcon(m_qtAwesome->icon(fa::fa_solid, fa::fa_square_plus));
    connect(ui->newExpenseButton, &QPushButton::pressed, this, [&]()
    {
        int32_t newModelIndex = 0;

        // This may need to be disabled and reenabled when adding rows
        // https://doc.qt.io/qt-6/qsortfilterproxymodel.html#dynamicSortFilter-prop
        m_expensesProxyModel->setDynamicSortFilter(false);

        m_expensesProxyModel->insertRow(newModelIndex);

        auto setValue = [&](int32_t viewIndex, LSExpenseModel::Columns column, auto value)
        {
            QModelIndex index = m_expensesProxyModel->index(viewIndex, static_cast<int>(column));
            m_expensesProxyModel->setData(index, value);
        };

        int32_t index = ui->categoryComboBox->currentIndex();
        QModelIndex modelIndex = m_categoryModel->index(index, static_cast<int>(categories::LSCategoryModel::Columns::id), {});
        int32_t const categoryId = m_categoryModel->data(modelIndex, Qt::DisplayRole).toInt();
        setValue(newModelIndex, LSExpenseModel::Columns::category, categoryId);

        setValue(newModelIndex, LSExpenseModel::Columns::recipient, ui->recipientLineEdit->text());
        setValue(newModelIndex, LSExpenseModel::Columns::amount, ui->amountDoubleSpinBox->value());

        //QModelIndex currentRecurringExpenseIndex = m_recurringModel->mapToSource( ui->recurringExpensesView->currentIndex() );
        QModelIndex currentRecurringExpenseIndex = ui->recurringExpensesView->currentIndex();
        int32_t recurringExpenseId = m_recurringModel->data(currentRecurringExpenseIndex, static_cast<int>(LSRecurringExpenseModel::Roles::IdRole)).toInt();
        setValue(newModelIndex, LSExpenseModel::Columns::relatedExpense, recurringExpenseId);

        // Suggest a date based on the global from date, the current month and the given billing day
        QDate suggestedDate = dateTime::constructValidDate(m_dateController->getFromDate().year(), QDate::currentDate().month(), ui->billingDaySpinBox->value());
        setValue(newModelIndex, LSExpenseModel::Columns::date, suggestedDate);

        m_expensesProxyModel->submit();

        m_expensesProxyModel->setDynamicSortFilter(true);
    });
}

LS::LSRecurringExpensesOverview::LSRecurringExpensesOverview(QWidget* parent, LSRelatedExpenseProxyModel* expensesProxyModel, LSCategoryFilterModel* recurringModel, QAbstractProxyModel* categoryModel, shared::LSDateController* dateController, QSettings* settings, fa::QtAwesome* qtAwesome) :
    QWidget(parent),
    ui(new Ui::RecurringExpensesOverview),
    m_dateController(dateController),
    m_recurringModel(recurringModel),
    m_expensesProxyModel(expensesProxyModel),
    m_categoryModel(categoryModel),
    m_settings(settings),
    m_qtAwesome(qtAwesome)
{
    ui->setupUi(this);

    QVariant const format = settings->value(application::ApplicationContext::LocaleDateFormatKey);

    ui->activeFromDateEdit->setDisplayFormat(format.toString());
    ui->activeToDateEdit->setDisplayFormat(format.toString());

    setUpMapper();
    setUpRecurringExpensesView();
    setUpRelatedExpensesView();

    m_toolBarItems = LSExpenseToolBarFactory::setUpToolbar(this, m_recurringModel, categoryModel, static_cast<int>(categories::LSCategoryModel::Columns::category), ui->recurringExpensesView, ui->toolBar, qtAwesome);

    ui->categoryComboBox->setModel(categoryModel);
    ui->categoryComboBox->setModelColumn(static_cast<int>(categories::LSCategoryModel::Columns::category));
}

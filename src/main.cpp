#include <QApplication>
#include <QDir>
#include <QFile>
#include <QIdentityProxyModel>
#include <QStringView>
#include <QStandardPaths>

#include "QtAwesome.h"

#include "categories/categorymodel.h"
#include "expenses/categoryfiltermodel.h"
#include "expenses/expensemodel.h"
#include "expenses/expensesoverviewwidget.h"
#include "expense_charts/aggregateexpensemodel.h"
#include "expense_charts/expensechartswidget.h"
#include "recurring_expenses/recurringexpensemodel.h"
#include "recurring_expenses/relatedexpenseproxymodel.h"

#include "settings/settingswidget.h"

#include "shared/applicationcontext.h"
#include "shared/database_manager.h"
#include "shared/datecontroller.h"
#include "shared/file_system/dir.h"

#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    using namespace LambdaSnail::Juno::expenses;
    using namespace LambdaSnail::Juno::shared;
    using namespace LambdaSnail::Juno::categories;
    using namespace LambdaSnail::QtExtensions;
    using namespace LambdaSnail::Juno::application;
    using namespace LambdaSnail::Juno::settings;

    QApplication a(argc, argv);
    QApplication::setApplicationName(ApplicationContext::ApplicationName);
    QApplication::setOrganizationName(ApplicationContext::OrganizationName);

    QSettings settings(ApplicationContext::OrganizationName, ApplicationContext::ApplicationName, &a);

    fa::QtAwesome* qtAwesome = new fa::QtAwesome();
    qtAwesome->initFontAwesome();


    QString const dbPath = settings.value(ApplicationContext::DbLocationSettingsKey, LSDir::joinPath(
                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0),
                                    ApplicationContext::ApplicationName_LowerCase))
                                 .toString();

    QString const dbFile = ApplicationContext::DbFileName;

    LSDatabaseManager db;
    qInfo() << "Using database at: " << LSDir::joinPath( dbPath, ApplicationContext::DbFileName);
    auto maybeError = db.setDatabase(dbPath, dbFile);

    if(maybeError)
    {
        qInfo() << maybeError.value().Message;
        return 1;
    }

    LSExpenseModel expenseModel;
    expenseModel.initialize();
    expenseModel.select();
    expenseModel.setEditStrategy(QSqlTableModel::EditStrategy::OnManualSubmit);

    LSRelatedExpenseProxyModel relatedExpenseProxyModel(&a);
    relatedExpenseProxyModel.setSourceModel(&expenseModel);


    LSRecurringExpenseModel recurringExpensesModel;
    recurringExpensesModel.initialize();
    recurringExpensesModel.setEditStrategy(QSqlTableModel::EditStrategy::OnFieldChange);

    LSCategoryFilterModel recurringCategoryFilterModel(&a, static_cast<int>(LSRecurringExpenseModel::Columns::category));
    recurringCategoryFilterModel.setSourceModel(&recurringExpensesModel);


    LSCategoryModel categoryModel;
    categoryModel.initialize();

    QIdentityProxyModel categoryProxyModel;
    categoryProxyModel.setSourceModel(&categoryModel);

    LSSettingsModel settingsModel(&settings, &a);
    LSSettingsWidget* settingsWidget = new LSSettingsWidget(&settingsModel);


    LSDateController dateController(expenseModel);


    auto* expensesOverviewWidget = new LSExpensesOverviewWidget(nullptr, nullptr/*statusBar()*/, &expenseModel, &categoryProxyModel, &settings, qtAwesome);
    auto* recurringExpensesWidget = new LSRecurringExpensesOverview(nullptr, &relatedExpenseProxyModel, &recurringCategoryFilterModel, &categoryProxyModel, &dateController, &settings, qtAwesome);

    auto aggregateExpenseModel = new LSAggregateExpenseModel(&categoryProxyModel);
    aggregateExpenseModel->setSourceModel(&expenseModel);
    auto* chartsWidget = new LambdaSnail::Juno::charts::LSExpenseChartsWidget(aggregateExpenseModel);

    LambdaSnail::Juno::LSMainWindow mainWindow(&categoryProxyModel, &dateController, &settings, expensesOverviewWidget, recurringExpensesWidget, chartsWidget, settingsWidget, qtAwesome);
    mainWindow.show();

    return QApplication::exec();
}

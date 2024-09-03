#include <QApplication>
#include <QDir>
#include <QFile>
#include <QIdentityProxyModel>
#include <QSettings>
#include <QStandardPaths>

#include "QtAwesome.h"

#include "categories/categorymodel.h"
#include "expenses/expensemodel.h"
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
    a.setApplicationName(ApplicationContext::ApplicationName);
    a.setOrganizationName(ApplicationContext::OrganizationName);

    QSettings settings(ApplicationContext::OrganizationName, ApplicationContext::ApplicationName, &a);

    fa::QtAwesome* qtAwesome = new fa::QtAwesome();
    qtAwesome->initFontAwesome();


    QString const dbPath = settings.value(ApplicationContext::DbLocationSettingsKey, LSDir::joinPath(
                                    QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0),
                                    ApplicationContext::ApplicationName_LowerCase))
                                 .toString();

    QString const dbFile = ApplicationContext::DbFileName;// LSDir::joinPath( dbPath, ApplicationContext::DbFileName);

    LSDatabaseManager db;
    qInfo() << "Using database at: " << LSDir::joinPath( dbPath, ApplicationContext::DbFileName);
    auto result = db.setDatabase(dbPath, dbFile);

    if(not result.has_value())
    {
        qInfo() << result.error().Message;
        return 1;
    }

    LSExpenseModel model;
    model.initialize();

    LSRelatedExpenseProxyModel relatedExpenseProyModel(&a);
    relatedExpenseProyModel.setSourceModel(&model);


    LSRecurringExpenseModel recurringExpensesModel;
    recurringExpensesModel.initialize();

    QIdentityProxyModel recurringExpensesAsProxyModel(&a);
    recurringExpensesAsProxyModel.setSourceModel(&recurringExpensesModel);


    LSCategoryModel categoryModel;
    categoryModel.initialize();

    QIdentityProxyModel categoryProxyModel;
    categoryProxyModel.setSourceModel(&categoryModel);

    LSSettingsModel settingsModel(&settings, &a);
    LSSettingsWidget* settingsWidget = new LSSettingsWidget(&settingsModel);


    LSDateController dateController(model);

    // Construct different pages here instead?

    LambdaSnail::Juno::LSMainWindow mainWindow(&model, &recurringExpensesAsProxyModel, &categoryProxyModel, &dateController, &relatedExpenseProyModel, &settings, settingsWidget, qtAwesome);
    mainWindow.show();

    return QApplication::exec();
}

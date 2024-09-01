#include <QApplication>
#include <QIdentityProxyModel>

#include "expenses/expensemodel.h"
#include "QtAwesome.h"
#include "categories/categorymodel.h"
#include "recurring_expenses/recurringexpensemodel.h"
#include "recurring_expenses/relatedexpenseproxymodel.h"
#include "shared/database_manager.h"
#include "shared/datecontroller.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    using namespace LambdaSnail::Juno::expenses;
    using namespace LambdaSnail::Juno::categories;

    QApplication a(argc, argv);

    fa::QtAwesome* qtAwesome = new fa::QtAwesome();
    qtAwesome->initFontAwesome();

    LambdaSnail::Juno::shared::LSDatabaseManager db;
    auto result = db.setDatabase("test.db");

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


    LambdaSnail::Juno::shared::LSDateController dateController(model);

    // Construct different pages here instead?

    LambdaSnail::Juno::LSMainWindow mainWindow(&model, &recurringExpensesAsProxyModel, &categoryProxyModel, &dateController, &relatedExpenseProyModel, qtAwesome);
    mainWindow.show();

    return QApplication::exec();
}

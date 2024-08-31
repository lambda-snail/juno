#include <QApplication>
#include <QIdentityProxyModel>

#include "expenses/expensemodel.h"
#include "QtAwesome.h"
#include "recurring_expenses/recurringexpensemodel.h"
#include "recurring_expenses/relatedexpenseproxymodel.h"
#include "shared/database_manager.h"
#include "shared/datecontroller.h"
#include "ui/mainwindow.h"



int main(int argc, char *argv[]) {
    using namespace LambdaSnail::Juno::expenses;



    QDate date(2020, 2, 28);
    qInfo() << date.toString();
    return 0;

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

    // This may need to be disabled and reenabled when adding rows
    // https://doc.qt.io/qt-6/qsortfilterproxymodel.html#dynamicSortFilter-prop
    //relatedExpenseProyModel.setDynamicSortFilter(true);

    LSRecurringExpenseModel recurringExpensesModel;
    recurringExpensesModel.initialize();

    QIdentityProxyModel recurringExpensesAsProxyModel(&a);
    recurringExpensesAsProxyModel.setSourceModel(&recurringExpensesModel);

    LambdaSnail::Juno::shared::LSDateController dateController(model);

    // Construct different pages here instead?

    LambdaSnail::Juno::LSMainWindow mainWindow(&model, &recurringExpensesAsProxyModel, &dateController, &relatedExpenseProyModel, qtAwesome);
    mainWindow.show();

    return QApplication::exec();
}

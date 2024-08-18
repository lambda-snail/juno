#include <QApplication>

#include "expenses/expensemodel.h"
#include "shared/database_manager.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    using namespace LambdaSnail::Juno::expenses;

    QApplication a(argc, argv);
    // QPushButton button("Hello world!", nullptr);
    // button.resize(200, 100);
    // button.show();
    // return QApplication::exec();

    LambdaSnail::Juno::shared::LSDatabaseManager db;
    auto result = db.setDatabase("test.db");

    LSExpenseModel model;
    model.initialize();

    LambdaSnail::Juno::LSMainWindow mainWindow(&model);
    mainWindow.show();

    return QApplication::exec();
}

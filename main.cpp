#include <QApplication>
#include <QSystemTrayIcon>

#include "expenses/expensemodel.h"
#include "external/QtAwesome/QtAwesome/QtAwesome.h"
#include "shared/database_manager.h"
#include "ui/mainwindow.h"



int main(int argc, char *argv[]) {
    using namespace LambdaSnail::Juno::expenses;

    QApplication a(argc, argv);
    // QPushButton button("Hello world!", nullptr);
    // button.resize(200, 100);
    // button.show();
    // return QApplication::exec();

    fa::QtAwesome* qtAwesome = new fa::QtAwesome();
    qtAwesome->initFontAwesome();

    LambdaSnail::Juno::shared::LSDatabaseManager db;
    auto result = db.setDatabase("test.db");

    LSExpenseModel model;
    model.initialize();

    qInfo() << QSystemTrayIcon::isSystemTrayAvailable();

    LambdaSnail::Juno::LSMainWindow mainWindow(&model, qtAwesome);
    mainWindow.show();

    return QApplication::exec();
}

#include <QApplication>
#include <QPushButton>
#include <QtSql/QSqlDatabase>

#include "src/shared/database_manager.h"
#include "ui/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // QPushButton button("Hello world!", nullptr);
    // button.resize(200, 100);
    // button.show();
    // return QApplication::exec();

    LambdaSnail::Juno::shared::LSDatabaseManager db;
    auto result = db.setDatabase("test.db");

    LambdaSnail::Juno::LSMainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}

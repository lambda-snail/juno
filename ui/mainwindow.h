//
// Created by niclas on 8/15/24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractTableModel>
#include <QMainWindow>

#include "expenses/expensemodel.h"

namespace LambdaSnail::Juno {
QT_BEGIN_NAMESPACE
namespace Ui { class LSMainWindow; }
QT_END_NAMESPACE

class LSMainWindow : public QMainWindow {
Q_OBJECT

public:
void setUpToolMenu();

    explicit LSMainWindow(expenses::LSExpenseModel* expenseModel);
    ~LSMainWindow() override;

private:
    Ui::LSMainWindow *ui;

    expenses::LSExpenseModel* m_expenseModel;
};
} // LambdaSnail::Juno

#endif //MAINWINDOW_H

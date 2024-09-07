//
// Created by niclas on 9/7/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_aboutwidget.h" resolved

#include "aboutwidget.h"
#include "ui_aboutwidget.h"

namespace LambdaSnail::Juno
{
    LSAboutWidget::LSAboutWidget(QWidget *parent) : QDialog(parent), ui(new Ui::LSAboutWidget)
    {
        ui->setupUi(this);
        setWindowTitle(tr("About Juno"));
    }

    LSAboutWidget::~LSAboutWidget()
    {
        delete ui;
    }
}

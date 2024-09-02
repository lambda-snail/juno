#include "settingswidget.h"
#include "ui_settingswidget.h"

namespace LambdaSnail::Juno::settings
{
    LSSettingsWidget::LSSettingsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LSSettingsWidget)
    {
        ui->setupUi(this);
    }

    LSSettingsWidget::~LSSettingsWidget()
    {
        delete ui;
    }
}

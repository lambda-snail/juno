#include <QDataWidgetMapper>
#include <QFileDialog>

#include "settingswidget.h"
#include "ui_settingswidget.h"

#include "settingsmodel.h"

namespace LambdaSnail::Juno::settings
{
    LSSettingsWidget::LSSettingsWidget(LSSettingsModel *settingsModel, QWidget *parent) : QWidget(parent),
        ui(new Ui::LSSettingsWidget), m_settingsModel(settingsModel), m_mapper(nullptr)
    {
        ui->setupUi(this);
        ui->dbFileInput->setReadOnly(true);

        setupMapper();
    }

    LSSettingsWidget::~LSSettingsWidget()
    {
        delete ui;
    }

    void LSSettingsWidget::setupMapper()
    {
        m_mapper = new QDataWidgetMapper(this);
        m_mapper->setModel(m_settingsModel);
        m_mapper->setSubmitPolicy(QDataWidgetMapper::SubmitPolicy::ManualSubmit);

        m_mapper->addMapping(ui->dbFileInput, static_cast<int>(LSSettingsModel::Columns::DatabaseFolder));
        m_mapper->addMapping(ui->dateFormatInput, static_cast<int>(LSSettingsModel::Columns::DateFormat));

        m_mapper->setCurrentIndex(LSSettingsModel::SettingsRow);

        connect(ui->saveSettingsButton, &QPushButton::clicked, [this]()
        {
            m_mapper->submit();
        });

        connect(ui->dbFileButton, &QPushButton::clicked, [this]()
        {
            QString newDir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), ui->dbFileInput->text());
            if(not newDir.isEmpty())
            {
                ui->dbFileInput->setText(newDir);
            }
        });
    }
}

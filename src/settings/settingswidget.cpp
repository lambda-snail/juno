#include "settingswidget.h"

#include "settingsmodel.h"
#include "ui_settingswidget.h"

#include <QDataWidgetMapper>
#include <QFileDialog>

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

        m_mapper->setCurrentIndex(0);

        connect(ui->saveSettingsButton, &QPushButton::clicked, [this]()
        {
            m_mapper->submit();
        });

        connect(ui->dbFileButton, &QPushButton::clicked, [this]()
        {
            QString newDir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), ui->dbFileInput->text());

            qInfo() << newDir;

            if(not newDir.isEmpty())
            {
                ui->dbFileInput->setText(newDir);
            }
        });
    }
}

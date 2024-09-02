//
// Created by niclas on 9/2/24.
//

#pragma once

#include <QWidget>

namespace LambdaSnail::Juno::settings
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class LSSettingsWidget;
    }

    QT_END_NAMESPACE

    class LSSettingsWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit LSSettingsWidget(QWidget *parent = nullptr);

        ~LSSettingsWidget() override;

    private:
        Ui::LSSettingsWidget *ui;
    };
}

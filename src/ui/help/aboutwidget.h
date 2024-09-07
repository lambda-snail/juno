#pragma once

#include <QDialog>

namespace LambdaSnail::Juno
{
    QT_BEGIN_NAMESPACE

    namespace Ui
    {
        class LSAboutWidget;
    }

    QT_END_NAMESPACE

    class LSAboutWidget : public QDialog
    {
        Q_OBJECT

    public:
        explicit LSAboutWidget(QWidget *parent = nullptr);

        ~LSAboutWidget() override;

    private:
        Ui::LSAboutWidget *ui;
    };
}

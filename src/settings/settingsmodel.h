#pragma once
#include <QAbstractItemModel>
#include <QSettings>

namespace LambdaSnail::Juno::settings
{
    /**
     * Exposes user-editable QSettings as an item model so that we can use QDataWidgetMapper to map to widgets.
     */
    class LSSettingsModel : public QAbstractItemModel
    {
        Q_OBJECT
    public:
        explicit LSSettingsModel(QSettings* settings, QObject* parent);

        [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
        [[nodiscard]] int columnCount(const QModelIndex &parent) const override;
        [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role) override;

        enum class Settings
        {
            DatabaseFolder
        };

    private:
        QSettings* m_settings;
    };
}

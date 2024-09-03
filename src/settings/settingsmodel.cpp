//
// Created by niclas on 9/2/24.
//

#include "settingsmodel.h"

#include <QStandardPaths>

#include "shared/applicationcontext.h"
#include "shared/file_system/dir.h"

namespace LambdaSnail::Juno::settings {
    LSSettingsModel::LSSettingsModel(QSettings* settings,QObject *parent) : QAbstractItemModel(parent), m_settings(settings)
    {
    }

    int LSSettingsModel::rowCount(const QModelIndex &parent) const
    {
        return 1;
    }

    int LSSettingsModel::columnCount(const QModelIndex &parent) const
    {
        return 1; // One per setting
    }

    QVariant LSSettingsModel::data(const QModelIndex &index, int role) const
    {
        if(role != Qt::DisplayRole and role != Qt::EditRole)
        {
            return {};
        }

        switch(index.column())
        {
            case static_cast<int32_t>(Columns::DatabaseFolder):
                return m_settings->value(application::ApplicationContext::DbLocationSettingsKey, QtExtensions::LSDir::joinPath(
                                      QStandardPaths::standardLocations(QStandardPaths::HomeLocation).at(0),
                                      application::ApplicationContext::ApplicationName_LowerCase));
            default:
                return {};
        }
    }

    bool LSSettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if(role != Qt::EditRole)
        {
            return false;
        }

        beginInsertRows(QModelIndex(), index.row(), index.column());

        switch(index.column())
        {
            case static_cast<int32_t>(Columns::DatabaseFolder):
                m_settings->setValue(application::ApplicationContext::DbLocationSettingsKey, value);
            default:
                std::unreachable();
        }

        endInsertRows();

        return true;
    }

    QModelIndex LSSettingsModel::index(int row, int column, const QModelIndex &parent) const
    {
        return createIndex(row, column);
    }

    QModelIndex LSSettingsModel::parent(const QModelIndex &child) const
    {
        return {};
    }
}

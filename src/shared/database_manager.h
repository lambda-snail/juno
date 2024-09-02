#pragma once

#include <expected>
#include <qsettings.h>
#include <QSqlDatabase>

namespace LambdaSnail::Juno::shared {
    class LSDatabaseManager {
    public:
        struct LSDatabaseError
        {
            explicit LSDatabaseError(QString const& message) : Message(message) {  }
            QString Message;
        };

        explicit LSDatabaseManager();
        std::expected<void, LSDatabaseError> setDatabase(QString const &path, QString const &databaseName);
    private:
        QSqlDatabase m_database;
    };
}

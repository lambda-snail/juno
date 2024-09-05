#pragma once

#include <expected>
#include <QSettings>
#include <QSqlDatabase>
#include <utility>

namespace LambdaSnail::Juno::shared {
    class LSDatabaseManager {
    public:
        struct LSDatabaseError
        {
            explicit LSDatabaseError(QString message) : Message(std::move(message)) {  }
            QString Message;
        };

        explicit LSDatabaseManager();
        std::expected<void, LSDatabaseError> setDatabase(QString const &path, QString const &databaseName);
    private:
        QSqlDatabase m_database;
    };
}

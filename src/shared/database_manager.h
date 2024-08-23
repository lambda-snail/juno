#pragma once

#include <expected>
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

        std::expected<void, LSDatabaseError> setDatabase(QString const& databaseName);

        enum class ExpenseColumns
        {
            id,
            date,
            recipient,
            description,
            category,
            amount,
            createdOn,
            modifiedOn
        };

    private:
        QSqlDatabase m_database;
    };
}

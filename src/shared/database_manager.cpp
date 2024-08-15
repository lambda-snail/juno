#include "database_manager.h"

#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

namespace LS = LambdaSnail::Juno::shared;

LS::LSDatabaseManager::LSDatabaseManager() = default;

std::expected<void, LS::LSDatabaseManager::LSDatabaseError>
LS::LSDatabaseManager::setDatabase(QString const &databaseName)
{
    assert(not databaseName.isEmpty());

    if (m_database.isOpen())
    {
        m_database.close();
    }

    bool isCreate = not QFile::exists(databaseName);

    // TODO: Support other vendors and user-provided database?
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);

    if (not db.open())
    {
        return std::unexpected<LSDatabaseError>(db.lastError().text());
    }

    // TODO: Figure out a better way to handle this
    if (isCreate)
    {
        QSqlQuery query;

        auto result = query.exec(R"(
            create table expenses (
                id integer primary key,
                date varchar(10),
                recipient text,
                description text,
                category text,
                amount integer,

                createdon integer,
                modifiedon integer
            )
        )");

        if (not result)
        {
            auto le = db.lastError();
            return std::unexpected<LSDatabaseError>(le.text());
        }
    }

    return {};
}

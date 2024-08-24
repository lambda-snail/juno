#include "database_manager.h"

#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

#include "expenses/expensemodel.h"

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

    if (isCreate)
    {
        QSqlQuery query(expenses::LSExpenseModel::tableDefinition());
        if (not query.exec())
        {
            auto le = db.lastError();
            return std::unexpected<LSDatabaseError>(le.text());
        }
    }

    return {};
}

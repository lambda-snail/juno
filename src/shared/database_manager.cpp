#include "database_manager.h"

#include <QFile>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>

#include "applicationcontext.h"
#include "categories/categorymodel.h"
#include "expenses/expensemodel.h"
#include "file_system/dir.h"
#include "recurring_expenses/recurringexpensemodel.h"

namespace LS = LambdaSnail::Juno::shared;

LS::LSDatabaseManager::LSDatabaseManager() = default;

std::optional<LS::LSDatabaseManager::LSDatabaseError>
LS::LSDatabaseManager::setDatabase(QString const& path, QString const& databaseName)
{
    assert(not databaseName.isEmpty());

    if (m_database.isOpen())
    {
        m_database.close();
    }

    QDir directory(path);
    bool isCreate = not QFileInfo::exists(directory.filePath(databaseName));
    if(not directory.exists())
    {
        bool pathCreated = directory.mkpath(path);
        if(not pathCreated)
        {
            return { LSDatabaseError("Unable to create directory: " + path) };
        }
    }

    // TODO: Support other vendors and user-provided database?
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(directory.filePath(databaseName));

    if (not db.open())
    {
        return { LSDatabaseError(db.lastError().text()) };
    }

    if (isCreate)
    {
        // Note that QSqlQuery executes the query on construction

        QSqlQuery recurringExpensesTableDefinition(expenses::LSRecurringExpenseModel::tableDefinition());
        if (recurringExpensesTableDefinition.lastError().isValid())
        {
            return { LSDatabaseError(recurringExpensesTableDefinition.lastError().text()) };
        }

        QSqlQuery categoryTableDefinition(categories::LSCategoryModel::tableDefinition());
        if (categoryTableDefinition.lastError().isValid())
        {
            return { LSDatabaseError(categoryTableDefinition.lastError().text()) };
        }

        QSqlQuery expensesTableDefinition(expenses::LSExpenseModel::tableDefinition());
        if (expensesTableDefinition.lastError().isValid())
        {
            return { LSDatabaseError(expensesTableDefinition.lastError().text()) };
        }
    }

    m_database = db;

    return std::nullopt;
}

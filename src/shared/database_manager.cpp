#include "database_manager.h"

#include <QFile>
#include <QSqlError>
#include <QSqlQuery>

#include "categories/categorymodel.h"
#include "expenses/expensemodel.h"
#include "recurring_expenses/recurringexpensemodel.h"

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
        // Note that QSqlQuery executes the query on construction

        QSqlQuery recurringExpensesTableDefinition(expenses::LSRecurringExpenseModel::tableDefinition());
        if (recurringExpensesTableDefinition.lastError().isValid())
        {
            return std::unexpected<LSDatabaseError>(recurringExpensesTableDefinition.lastError().text());
        }

        QSqlQuery categoryTableDefinition(categories::LSCategoryModel::tableDefinition());
        if (categoryTableDefinition.lastError().isValid())
        {
            return std::unexpected<LSDatabaseError>(categoryTableDefinition.lastError().text());
        }

        QSqlQuery expensesTableDefinition(expenses::LSExpenseModel::tableDefinition());
        if (expensesTableDefinition.lastError().isValid())
        {
            return std::unexpected<LSDatabaseError>(expensesTableDefinition.lastError().text());
        }
    }

    return {};
}

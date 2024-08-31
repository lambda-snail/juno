#pragma once
#include <QSqlTableModel>

namespace LambdaSnail::Juno::categories
{
    class LSCategoryModel : public QSqlTableModel
    {
        Q_OBJECT

    public:
        void initialize();

        [[nodiscard]] static QSqlQuery tableDefinition();

        enum class Columns
        {
            id,
            category
        };
    };
}

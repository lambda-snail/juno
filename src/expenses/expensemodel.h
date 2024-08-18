#pragma once

#include <QSqlTableModel>

namespace LambdaSnail::Juno::expenses
{
    class LSExpenseModel : public QSqlTableModel
    {
    public:
        void initialize();

    };
}

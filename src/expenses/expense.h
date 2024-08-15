#pragma once

#include <QDate>

namespace LambdaSnail::Juno::expenses {

    typedef uint64_t ExpenseHandle;

    struct LSExpense {
        ExpenseHandle Id;

        QDate Date;
        QString Recipient;
        QString Description;
        QString Category;   // TODO: Own table
        int Amount;         // TODO: Money class

        QDate CreatedOn;
        QDate ModifiedOn;
    };
}

//
// Created by niclas on 8/15/24.
//

#include "expensemodel.h"

namespace LS = LambdaSnail::Juno::expenses;

void LS::LSExpenseModel::initialize()
{
    setTable("expenses");
    select();
}

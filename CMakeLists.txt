cmake_minimum_required(VERSION 3.28)
project(juno)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# If cmake configuration fails, remember to set the -DCMAKE_PREFIX_PATH to point to the
# Qt directory. Examples: /opt/Qt/6.7.2/gcc_64 (Linux), C:/Qt/6.7.2/msvc2019_64 (Windows)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wformat=2 -Wconversion -Wimplicit-fallthrough")

#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
endif()

find_package(Qt6 COMPONENTS
        Core
        Charts
        Gui
        Widgets
        Sql
        REQUIRED)

add_subdirectory(external)

add_executable(juno src/main.cpp
        src/expenses/expense.h
        src/shared/database_manager.cpp
        src/shared/database_manager.h

        src/ui/mainwindow.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.ui

        src/expenses/expensemodel.cpp
        src/expenses/expensemodel.h
        src/expenses/expensesoverviewwidget.cpp
        src/expenses/expensesoverviewwidget.h
        src/expenses/expensesoverviewwidget.ui
        src/shared/date_time/datefromstringdelegate.cpp
        src/shared/date_time/datefromstringdelegate.h

        src/recurring_expenses/recurringexpensemodel.cpp
        src/recurring_expenses/recurringexpensemodel.h
        src/recurring_expenses/recurringexpensesoverview.cpp
        src/recurring_expenses/recurringexpensesoverview.h
        src/recurring_expenses/recurringexpensesoverview.ui
        src/recurring_expenses/relatedexpenseproxymodel.cpp
        src/recurring_expenses/relatedexpenseproxymodel.h
        src/shared/datecontroller.cpp
        src/shared/datecontroller.h
        src/shared/date_time/datetimehelpers.h
        src/expense_charts/expensechartswidget.cpp
        src/expense_charts/expensechartswidget.h
        src/expense_charts/expensechartswidget.ui
        src/expense_charts/aggregateexpensemodel.cpp
        src/expense_charts/aggregateexpensemodel.h
        src/categories/categorymodel.cpp
        src/categories/categorymodel.h
        src/shared/file_system/dir.cpp
        src/shared/file_system/dir.h
        src/shared/applicationcontext.h
        src/shared/applicationcontext.cpp
        src/settings/settingswidget.cpp
        src/settings/settingswidget.h
        src/settings/settingswidget.ui
        src/settings/settingsmodel.cpp
        src/settings/settingsmodel.h
        src/shared/currency/expensemodelbase.cpp
        src/shared/currency/expensemodelbase.h
        src/expenses/categoryfiltermodel.cpp
        src/expenses/categoryfiltermodel.h
        src/ui/help/aboutwidget.cpp
        src/ui/help/aboutwidget.h
        src/ui/help/aboutwidget.ui
        src/expenses/expensetoolbarfactory.h
        src/shared/delegates/relationalproxydelegate.cpp
        src/shared/delegates/relationalproxydelegate.h
        src/budget/budgetoverviewwidget.cpp
        src/budget/budgetoverviewwidget.h
        src/budget/budgetoverviewwidget.ui
        src/budget/budgetcategorybar.cpp
        src/budget/budgetcategorybar.h
        src/budget/budgetcategorybar.ui
)

# https://cmake.org/cmake/help/v3.9/prop_tgt/AUTOGEN_BUILD_DIR.html#prop_tgt:AUTOGEN_BUILD_DIR
set(LS_AUTOGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/juno_autogen)
message(${LS_AUTOGEN_DIR})

target_include_directories(juno PRIVATE src LS_AUTOGEN_DIR/include)

target_link_libraries(juno
        PRIVATE
        Qt::Core
        Qt::Charts
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        QtAwesome
)


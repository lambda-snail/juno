cmake_minimum_required(VERSION 3.28)
project(juno)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/Qt/6.7.2/gcc_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

add_subdirectory(external)

add_executable(juno main.cpp
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
        src/expenses/datefromstringdelegate.cpp
        src/expenses/datefromstringdelegate.h

)

# https://cmake.org/cmake/help/v3.9/prop_tgt/AUTOGEN_BUILD_DIR.html#prop_tgt:AUTOGEN_BUILD_DIR
set(LS_AUTOGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/juno_autogen)
message(${LS_AUTOGEN_DIR})

target_include_directories(juno PRIVATE src LS_AUTOGEN_DIR/include)

target_link_libraries(juno
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
        QtAwesome
)


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

add_executable(juno main.cpp
        src/expenses/expense.h
        src/shared/database_manager.cpp
        src/shared/database_manager.h
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui

)

target_link_libraries(juno
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql
)


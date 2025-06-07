cmake_minimum_required(VERSION 3.16)

project(IP_Info_App
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматический moc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Найти Qt6-модули
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
)

qt_standard_project_setup()

qt_add_executable(IP_Info_App
    main.cpp
    IpInfoWidget.h
    IpInfoWidget.cpp
    IpInfoWidget.ui
)

target_link_libraries(IP_Info_App PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
)

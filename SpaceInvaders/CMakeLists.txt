cmake_minimum_required(VERSION 3.14)

project(SpaceInvaders LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Gui Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui Multimedia REQUIRED)

add_executable(SpaceInvaders WIN32
    main.cpp src.qrc
    game.cpp game.h
    unit.cpp unit.h
    enemy.cpp enemy.h
    bullet.h bullet.cpp
    defender.h defender.cpp
    )
target_link_libraries(SpaceInvaders
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Multimedia
    )

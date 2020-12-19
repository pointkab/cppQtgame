cmake_minimum_required(VERSION 3.16)
project(QtGame)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH D:/Qt/5.14.2/mingw73_64) #这里需要填入自己安装的路径
set(Qt5_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt5")
set(Qt5Widgets_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt5Widgets")
set(Qt5LinguistTools_DIR "${CMAKE_PREFIX_PATH}/lib/cmake/Qt5LinguistTools")

find_package(Qt5Widgets)
find_package( Qt5Core)
find_package( Qt5Gui)

set(UI_FILES)

set(RC_FILES)

set(QRC_FILES)

set(SOURCE_FILES main.cpp mainwindow.cpp mainwindow.h)

add_executable(QtGame WIN32 main.cpp mainwindow.cpp mainwindow.h mainwindow.ui GameUi.cpp GameUi.h Role.h PlayerRole.cpp PlayerRole.h MonsterRole.cpp MonsterRole.h Attack.cpp Attack.h)

target_link_libraries(QtGame Qt5::Widgets)

qt5_use_modules(QtGame Core Widgets Gui)
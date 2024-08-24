cmake_minimum_required(VERSION 3.5)

project(Calc VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

set(PROJECT_SOURCES
    main.cpp

    main_window.cpp
    main_window.h
    mainwindow.ui

    graphic.h
    graphic.cpp
    graphic.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(Calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts)
target_link_libraries(Calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/s21_calculator.a)
target_link_libraries(Calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/s21_list.a)
target_link_libraries(Calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/s21_stack.a)

set_target_properties(Calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Calc)
endif()

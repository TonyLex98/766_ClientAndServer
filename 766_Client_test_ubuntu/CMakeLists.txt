cmake_minimum_required(VERSION 3.5)

project(766_Client_test_ubuntu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Svg SvgWidgets Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        CustomGraphicScene.cpp
        CustomGraphicScene.h
        Sight.h
        Sight.cpp
        Images.qrc
        UdpClient.h
        UdpClient.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(766_Client_test_ubuntu
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 766_Client_test_ubuntu APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(766_Client_test_ubuntu SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(766_Client_test_ubuntu
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(766_Client_test_ubuntu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(766_Client_test_ubuntu PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS 766_Client_test_ubuntu
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


target_link_libraries(766_Client_test_ubuntu PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Svg
    Qt::SvgWidgets
    Qt::Widgets
    Qt::Network
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(766_Client_test_ubuntu)
endif()

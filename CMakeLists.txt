cmake_minimum_required(VERSION 3.0)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        WebEngineWidgets
        REQUIRED)

link_directories(
        #        /user/lib
)

add_executable(untitled
        window.cpp
        window.h
        main.cpp
        ui_window.h
        session.h
        session.cpp
        holdTcp.h
        holdTcp.cpp
        )
add_executable(test test.cpp)
target_link_libraries(untitled
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebEngineWidgets
        libcurl.so.4.8.0
        )
target_link_libraries(test
        libcurl.so.4.8.0
        )


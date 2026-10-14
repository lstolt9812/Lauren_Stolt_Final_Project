cmake_minimum_required(VERSION 3.23)
project(QtVTK LANGUAGES CXX VERSION 1.0.0)

find_package(Qt6 COMPONENTS Widgets Concurrent Gui OpenGLWidgets REQUIRED)
find_package(VTK REQUIRED)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${VTK_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ScientificDataLibrary
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        ${VTK_LIBRARIES}
)



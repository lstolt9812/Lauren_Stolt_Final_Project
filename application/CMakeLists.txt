find_package(
    Qt6
    COMPONENTS
        Widgets
        Gui
        OpenGL
        OpenGLWidgets
    REQUIRED
)

find_package(
    VTK
    REQUIRED
    COMPONENTS
        CommonCore
        CommonDataModel
        FiltersSources
        InteractionStyle
        RenderingCore
        RenderingOpenGL2
        GUISupportQt
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(CaterpillarSimulation)

target_sources(CaterpillarSimulation
    PRIVATE
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui
)

target_link_libraries(CaterpillarSimulation
    PRIVATE
        SimulationLibrary
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        ${VTK_LIBRARIES}
)

target_compile_features(CaterpillarSimulation
    PRIVATE
        cxx_std_17
)

vtk_module_autoinit(
    TARGETS CaterpillarSimulation
    MODULES ${VTK_LIBRARIES}
)
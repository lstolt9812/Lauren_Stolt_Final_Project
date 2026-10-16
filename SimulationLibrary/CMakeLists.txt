add_library(SimulationLibrary)

target_sources(SimulationLibrary
    PRIVATE
        src/SimulationLibrary.cpp
    PUBLIC
        include/Position.hpp
)

target_include_directories(SimulationLibrary
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(SimulationLibrary
    PUBLIC
        cxx_std_17
)
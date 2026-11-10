add_library(SimulationLibrary
    include/Creature.hpp
    include/Food.hpp
    include/FoodGenerator.hpp
    include/MapBounds.hpp)

target_sources(SimulationLibrary
    PRIVATE
        src/SimulationLibrary.cpp
    PUBLIC
        include/Creature.hpp
        include/Food.hpp
        include/FoodGenerator.hpp
        include/MapBounds.hpp
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
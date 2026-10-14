add_library(ScientificDataLibrary)

target_sources(ScientificDataLibrary
    PRIVATE
        src/DataGenerator.cpp
    PUBLIC
        include/DataGenerator.hpp
)

target_include_directories(ScientificDataLibrary
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ScientificDataLibrary
    PUBLIC
        cxx_std_17
)


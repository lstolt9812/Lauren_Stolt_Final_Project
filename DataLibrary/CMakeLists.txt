add_library(DataLibrary
    include/DataGenerator.hpp
    src/DataGenerator.cpp
)

target_include_directories(DataLibrary PUBLIC include)


add_library(ScientificDataLibrary
src/DataGenerator.cpp
)

target_include_directories(ScientificDataLibrary
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(ScientificDataLibrary
PUBLIC
cxx_std_17
)

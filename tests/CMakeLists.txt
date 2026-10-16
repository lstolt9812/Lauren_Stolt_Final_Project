add_executable(mylibrary_unittests
    mylibrary_unittests.cpp
)

target_link_libraries(mylibrary_unittests
    PRIVATE
        SimulationLibrary
        gtest_main
)

target_compile_features(mylibrary_unittests
    PRIVATE
        cxx_std_17
)

include(GoogleTest)

gtest_discover_tests(mylibrary_unittests)

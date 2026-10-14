add_executable(mylibrary_unittests
    mylibrary_unittests.cpp
)

target_link_libraries(mylibrary_unittests
    PRIVATE
        DataLibrary
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(mylibrary_unittests)

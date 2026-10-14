cmake_minimum_required(VERSION 3.23)

project(QtVTK LANGUAGES CXX VERSION 1.0.0)

find_package(VTK REQUIRED)
# ----------------------------
# GoogleTest
# ----------------------------

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Required for Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# ----------------------------

add_subdirectory(application)
add_subdirectory(DataLibrary)
add_subdirectory(tests)

enable_testing()

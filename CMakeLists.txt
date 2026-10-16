cmake_minimum_required(VERSION 3.23)

project(
    LaurenStoltFinalProject
    VERSION 1.0.0
    LANGUAGES CXX
)

# GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Keep GoogleTest compatible with the Windows runtime used by this project.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_subdirectory(SimulationLibrary)
add_subdirectory(application)

enable_testing()
add_subdirectory(tests)
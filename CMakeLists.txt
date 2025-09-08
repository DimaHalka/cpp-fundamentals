cmake_minimum_required(VERSION 3.14)

project(cpp-fundamentals)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library data_structures
add_library(cpp-fundamentals INTERFACE
    unique_ptr.hpp
)

# GoogleTest 
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")
set(BUILD_GMOCK OFF CACHE BOOL "Disable GoogleMock")
set(INSTALL_GMOCK OFF CACHE BOOL "Disable installing GoogleMock")
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(unit_tests
    test_unique_ptr.cpp
)
target_link_libraries(unit_tests
    GTest::gtest_main
    cpp-fundamentals
)
include(GoogleTest)

gtest_discover_tests(unit_tests
  DISCOVERY_MODE PRE_TEST
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)


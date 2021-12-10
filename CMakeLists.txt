cmake_minimum_required(VERSION 3.20)

project(PowerManagementUnit)

set(CMAKE_C_STANDARD 99)

# Check for CppUTest and bail out if they don't have it
if(DEFINED ENV{CPPUTEST_HOME} AND DEFINED ENV{CPPUTESTEXT_HOME} AND DEFINED ENV{CPPUTEST_PARENT_DIR})
    message("Using CppUTest found in $ENV{CPPUTEST_HOME}")
    message("Using CppUTest Extensions found in $ENV{CPPUTESTEXT_HOME}")
    message("Using CppUTest library basedir found in $ENV{CPPUTEST_PARENT_DIR}")
else()
    message("CPPUTEST_HOME or CPPUTESTEXT_HOME or CPPUTEST_PARENT_DIR is not set; You must tell CMake where to find CppUTest")
    return()
endif()

enable_language(C)
enable_language(CXX)

# The version number
set (PowerManagementUnit_VERSION_MAJOR 1)
set (PowerManagementUnit_VERSION_MINOR 0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)
add_subdirectory(mocks)
add_subdirectory(test)


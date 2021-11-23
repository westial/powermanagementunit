cmake_minimum_required(VERSION 3.20)

project(PowerManagementUnit)

set(CMAKE_C_STANDARD 99)

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


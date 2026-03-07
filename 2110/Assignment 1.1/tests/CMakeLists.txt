cmake_minimum_required(VERSION 3.14)
project(LibraryManagementTests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GoogleTest
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../googletest-v1.17.0 ${CMAKE_CURRENT_BINARY_DIR}/googletest)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add source files
set(SOURCES
    ../Book.cpp
    ../Library.cpp
)

# Add test executable
add_executable(run_tests
    library_test.cpp
    ${SOURCES}
)

# Link GoogleTest
target_link_libraries(run_tests gtest gtest_main)

# Enable testing
enable_testing()
add_test(NAME LibraryTests COMMAND run_tests)

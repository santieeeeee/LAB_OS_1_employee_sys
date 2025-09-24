# test/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Add googletest from external/googletest (user must populate this folder via git submodule or manual download)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/googletest ${CMAKE_BINARY_DIR}/external/googletest)

# Create tests executable
add_executable(employee_tests
    employee_tests.cpp
)

# Link with project library and gtest
target_link_libraries(employee_tests
    PRIVATE
        employee_lib
        gtest_main
)

# Enable discovery of tests by CTest
include(GoogleTest)
gtest_discover_tests(employee_tests)

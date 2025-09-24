# src/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Библиотека с логикой employee
add_library(employee_lib STATIC
    employee.cpp
    employee.h
)

target_include_directories(employee_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Утилиты и main
add_executable(Creator Creator.cpp)
target_link_libraries(Creator PRIVATE employee_lib)

add_executable(Reporter Reporter.cpp)
target_link_libraries(Reporter PRIVATE employee_lib)

add_executable(Main Main.cpp)
target_link_libraries(Main PRIVATE employee_lib)

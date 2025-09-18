cmake_minimum_required(VERSION 3.14)
project(EmployeeProcesses LANGUAGES CXX)

# 1.1 Общие настройки
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1.2 Папка для бинарников
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1.3 Подключаем поддиректории
add_subdirectory(src)
add_subdirectory(tests)

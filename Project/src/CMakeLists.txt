# src/CMakeLists.txt

# 2.1 Файлы с исходниками
set(SOURCES
    Creator.cpp
    Reporter.cpp
    Main.cpp
)

# 2.2 Утилита Creator
add_executable(Creator Creator.cpp)
target_compile_definitions(Creator PRIVATE WIN32_LEAN_AND_MEAN)
# при необходимости добавить include-директории:
# target_include_directories(Creator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# 2.3 Утилита Reporter
add_executable(Reporter Reporter.cpp)
target_compile_definitions(Reporter PRIVATE WIN32_LEAN_AND_MEAN)

# 2.4 Основная программа MainApp
add_executable(MainApp Main.cpp)
target_compile_definitions(MainApp PRIVATE WIN32_LEAN_AND_MEAN)

# Все exe окажутся в ${CMAKE_BINARY_DIR}/bin благодаря CMAKE_RUNTIME_OUTPUT_DIRECTORY

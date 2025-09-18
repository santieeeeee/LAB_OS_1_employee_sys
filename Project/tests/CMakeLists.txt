# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(UnitTests LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.10
)
FetchContent_MakeAvailable(catch2)

# Собираем UnitTests
add_executable(UnitTests
    tests.cpp
)

# Линкуем с Catch2 (генерирует main и всю инфраструктуру)
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)

# Включаем CTest и регистрируем наш тест
enable_testing()
add_test(NAME RunAllUnitTests COMMAND UnitTests)

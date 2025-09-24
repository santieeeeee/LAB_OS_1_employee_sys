cmake_minimum_required(VERSION 3.14)
project(lab_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к локальной копии googletest: помести репозиторий googletest в third_party/googletest
set(GOOGLETEST_ROOT "${CMAKE_SOURCE_DIR}/../third_party/googletest")
if(NOT EXISTS "${GOOGLETEST_ROOT}/CMakeLists.txt")
  message(FATAL_ERROR "Local googletest not found in ${GOOGLETEST_ROOT}. Clone googletest into third_party/googletest or adjust this file.")
endif()

# Отключаем сборку gmock, собираем только gtest (устраняет ошибки с отсутствующими include в gmock)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

# Для MSVC: заставить gtest использовать shared CRT
set(gtest_force_shared_crt ON CACHE BOOL "Force gtest to use shared CRT" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# Подключаем локальную копию googletest (будет собран только gtest)
add_subdirectory(${GOOGLETEST_ROOT} ${CMAKE_BINARY_DIR}/googletest_build)

# Автоматический поиск исходников проекта, которые нужны тестам.
# Ищем в двух местах: корень репозитория и папка src
set(POSSIBLE_DIRS
  "${CMAKE_SOURCE_DIR}/.."         # repo root
  "${CMAKE_SOURCE_DIR}/../src"     # src/
)

set(APP_SOURCES)
foreach(d IN LISTS POSSIBLE_DIRS)
  if(EXISTS "${d}")
    file(GLOB_RECURSE found_cpp RELATIVE "${d}" "${d}/*.cpp" "${d}/*.cxx" "${d}/*.cc")
    foreach(f IN LISTS found_cpp)
      # исключаем потенциальные тестовые или билд-артефакты внутри директорий tests/build и third_party
      if(NOT f MATCHES "tests/" AND NOT f MATCHES "build/" AND NOT f MATCHES "third_party/")
        list(APPEND APP_SOURCES "${d}/${f}")
      endif()
    endforeach()
  endif()
endforeach()

# Убираем файлы с main из списка, чтобы не было конфликтов (по именам common в твоём проект: Main.cpp, Creator.cpp, Reporter.cpp)
if(APP_SOURCES)
  foreach(exe_main IN ITEMS "${CMAKE_SOURCE_DIR}/../Main.cpp" "${CMAKE_SOURCE_DIR}/../Creator.cpp" "${CMAKE_SOURCE_DIR}/../Reporter.cpp")
    list(REMOVE_ITEM APP_SOURCES ${exe_main})
  endforeach()
endif()

# Добавляем тестовый раннер
add_executable(tests_runner
  test_employee.cpp
  ${APP_SOURCES}
)

# Инклуд-пути: добавляем корень репозитория и src (если нужны заголовки)
target_include_directories(tests_runner PRIVATE
  ${CMAKE_SOURCE_DIR}/..
  ${CMAKE_SOURCE_DIR}/../src
)

# Линкуем gtest_main
target_link_libraries(tests_runner PRIVATE gtest_main)

enable_testing()
add_test(NAME all_tests COMMAND tests_runner)

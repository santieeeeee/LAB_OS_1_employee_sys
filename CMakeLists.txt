cmake_minimum_required(VERSION 3.10)
project(LAB_OS_1_employee_sys LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматически собираем все .cpp внутри папок
file(GLOB CREATOR_SRCS "${CMAKE_SOURCE_DIR}/Creator/*.cpp")
file(GLOB REPORTER_SRCS "${CMAKE_SOURCE_DIR}/Reporter/*.cpp")
file(GLOB MAIN_SRCS "${CMAKE_SOURCE_DIR}/Main/*.cpp")

# Предупреждения, если ничего не найдено
if(NOT CREATOR_SRCS)
  message(WARNING "No Creator sources found in ${CMAKE_SOURCE_DIR}/Creator")
endif()
if(NOT REPORTER_SRCS)
  message(WARNING "No Reporter sources found in ${CMAKE_SOURCE_DIR}/Reporter")
endif()
if(NOT MAIN_SRCS)
  message(WARNING "No Main sources found in ${CMAKE_SOURCE_DIR}/Main")
endif()

# Создаём цели только если есть исходники
if(CREATOR_SRCS)
  add_executable(Creator ${CREATOR_SRCS})
endif()
if(REPORTER_SRCS)
  add_executable(Reporter ${REPORTER_SRCS})
endif()
if(MAIN_SRCS)
  add_executable(MainApp ${MAIN_SRCS})
endif()

# Общая папка для exe
set_target_properties(
  Creator Reporter MainApp PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

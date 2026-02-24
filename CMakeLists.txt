cmake_minimum_required(VERSION 3.20)
project(uuid LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(uuid INTERFACE)
add_library(uuid::uuid ALIAS uuid)

target_include_directories(uuid INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if (MSVC)
  target_compile_options(uuid INTERFACE /W4 /permissive-)
else()
  target_compile_options(uuid INTERFACE -Wall -Wextra -Wpedantic)
endif()

# --- Vix deps (secure_random) ---
include(.vix/vix_deps.cmake)
target_link_libraries(uuid INTERFACE gaspardkirira::secure_random)

include(CTest)
enable_testing()

add_executable(uuid_basic_test tests/test_basic.cpp)
target_link_libraries(uuid_basic_test PRIVATE uuid::uuid)
add_test(NAME uuid.basic COMMAND uuid_basic_test)

cmake_minimum_required(VERSION 3.10)
project(slot_machine_game C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

file(GLOB SOURCES 
    src/*.c
)

include_directories(include)

add_executable(game ${SOURCES})

find_package(raylib REQUIRED)
target_link_libraries(game raylib)
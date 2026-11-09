cmake_minimum_required(VERSION 4.3)
project(clib
        LANGUAGES C
        VERSION 0.1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CLIB ${CMAKE_PROJECT_NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CreateTestExes)

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

add_library(${CLIB} STATIC)
target_sources(${CLIB} PRIVATE
        ${LIB_SOURCES})
target_include_directories(${CLIB} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(${CLIB} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_compile_options(-Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined)
add_link_options(-fsanitize=address)

add_subdirectory(deps)

enable_testing()

add_subdirectory(tests)

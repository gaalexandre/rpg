cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(UnnamedRpg VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(-Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wshadow
  -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic
  -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference
  -Wdouble-promotion -Wformat=2 -Weffc++)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(-Weverything)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-Wduplicated-cond -Wduplicated-branches -Wlogical-op
	-Wuseless-cast)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
else()
  add_compile_options(-O2)
endif()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(main)

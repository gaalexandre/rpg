cmake_minimum_required(VERSION 3.20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CPM_DOWNLOAD_VERSION 0.35.1)

if(CPM_SOURCE_CACHE)
  set(CPM_DOWNLOAD_LOCATION
      "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
  set(CPM_DOWNLOAD_LOCATION
      "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
  set(CPM_DOWNLOAD_LOCATION
      "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
  file(
    DOWNLOAD
    https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION})
endif()

message(${CPM_DOWNLOAD_LOCATION})
include(${CPM_DOWNLOAD_LOCATION})

cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")

project(
  UnnamedRpg
  VERSION 0.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(
  -Werror
  -Wall
  -Wextra
  -Wshadow
  -Wnon-virtual-dtor
  -pedantic
  -Wshadow
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wmisleading-indentation
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
  -Weffc++)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_CLANG_TIDY clang-tidy)
  set(GCOV-EXECUTABLE "llvm-cov gcov")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-Wduplicated-cond -Wduplicated-branches -Wlogical-op
                      -Wuseless-cast)
  set(GCOV-EXECUTABLE "gcov")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(--coverage -O0 -g)
  add_link_options(--coverage)
else()
  add_compile_options(-O2)
endif()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(main)

add_custom_target(run main/main)
add_dependencies(run main)

add_custom_target(run-test test/test)
add_dependencies(run-test test)

add_custom_target(
  gcovr
  gcovr
  --exclude
  main
  --fail-under-line
  100
  --gcov-executable
  ${GCOV-EXECUTABLE}
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_dependencies(gcovr test)

add_custom_target(
  clear
  rm -rf build/* bin/*
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(full-test)
add_dependencies(full-test run-test gcovr check-format)

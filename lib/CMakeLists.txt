set(LIB_FILES lib.cpp lib.h GameLoop.hpp)

add_library(lib ${LIB_FILES})

add_subdirectory(rendering)
add_subdirectory(ecs)

target_include_directories(lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

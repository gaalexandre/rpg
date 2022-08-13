target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(lib PRIVATE Archetype.hpp EntityId.h EntityId.cpp)
add_subdirectory(sparseSet)

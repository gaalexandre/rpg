target_sources(
  test PRIVATE ecs_test.h ecs_test.cpp Archetype_test.h Archetype_test.cpp
               EntityId_test.h EntityId_test.cpp)

add_subdirectory(sparseSet)

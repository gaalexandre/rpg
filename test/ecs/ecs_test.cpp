#include "ecs_test.h"
#include "Archetype_test.h"
#include "EntityId_test.h"
#include "sparseSet/sparseSet_test.h"

void testEcs() {
    testEntityId();
    testArchetype();
    testSparseSet();
}

#include "ecs/ecs_test.h"
#include "GameLoop_test.h"
#include "rendering/rendering_test.h"
#include <boost/ut.hpp>

int main() {
    testGameLoop();
    testRendering();
    testEcs();
    return 0;
}

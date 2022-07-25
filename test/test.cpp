#include "GameLoop_test.h"
#include "rendering/rendering_test.h"
#include <boost/ut.hpp>

int main() {
    testGameLoop();
    testRendering();
    return 0;
}

#include "Renderer_test.h"
#include "Renderer.hpp"
#include <boost/ut.hpp>

class FakeGraphicsRenderer {
public:
    void renderGraphics() { ++m_nbCalls; }

    [[nodiscard]] unsigned int nbCalls() const { return m_nbCalls; };

private:
    unsigned int m_nbCalls = 0;
};

void testRenderer() {
    using namespace boost::ut;

    "Test render method"_test = []() {
        FakeGraphicsRenderer fakeGraphicsRenderer;
        Renderer renderer{fakeGraphicsRenderer};
        renderer.render();
        expect(fakeGraphicsRenderer.nbCalls() == 1_u)
            << "Did not call GraphicsRenderer correctly.";
    };
}

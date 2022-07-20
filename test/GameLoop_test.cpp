#include "GameLoop.hpp"
#include <boost/ut.hpp>

namespace {
class ExitAfterNIterations {
public:
    explicit ExitAfterNIterations(unsigned int counter) : m_counter{counter} {}

    [[nodiscard]] bool shouldExitGame() { return m_counter-- == 0; }

private:
    unsigned int m_counter;
};

class FakeDecisionTaker {
public:
    void takeDecisions() { ++m_nbCalls; }

    [[nodiscard]] unsigned int nbCalls() const { return m_nbCalls; };

private:
    unsigned int m_nbCalls = 0;
};

class FakePhysicsCalculator {
public:
    void computePhysics() { ++m_nbCalls; }

    [[nodiscard]] unsigned int nbCalls() const { return m_nbCalls; };

private:
    unsigned int m_nbCalls = 0;
};

class FakeRenderer {
public:
    void render() { ++m_nbCalls; }

    [[nodiscard]] unsigned int nbCalls() const { return m_nbCalls; };

private:
    unsigned int m_nbCalls = 0;
};

}

void testGameLoop() {
    using namespace boost::ut;

    "N GameLoop Run"_test = [](unsigned int nbExpectedCalls) {
        FakeDecisionTaker fakeDecisionTaker;
        FakePhysicsCalculator fakePhysicsCalculator;
        FakeRenderer fakeRenderer;
        GameLoop gameLoop{fakeDecisionTaker, fakePhysicsCalculator, fakeRenderer};

        ExitAfterNIterations exiter{nbExpectedCalls};
        gameLoop.run(exiter);

        expect(eq(fakeDecisionTaker.nbCalls(), nbExpectedCalls))
            << "Did not call DecisionTaker correctly.";
        expect(eq(fakePhysicsCalculator.nbCalls(), nbExpectedCalls))
            << "Did not call PhysicsCalculator correctly.";
        expect(eq(fakeRenderer.nbCalls(), nbExpectedCalls))
            << "Did not call Renderer correctly.";
    } | std::array{0, 1, 10};
}

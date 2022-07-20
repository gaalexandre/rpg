#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP

#include <concepts>

template<typename T>
concept CanDecide = requires(T type) {
                        { type.takeDecisions() } -> std::same_as<void>;
                    };

template<typename T>
concept CanComputePhysics = requires(T type) {
                                { type.computePhysics() } -> std::same_as<void>;
                            };

template<typename T>
concept CanRender = requires(T type) {
                        { type.render() } -> std::same_as<void>;
                    };

template<typename T>
concept CanExitGame = requires(T type) {
                          { type.shouldExitGame() } -> std::same_as<bool>;
                      };

template<CanDecide DecisionTaker, CanComputePhysics PhysicsCalculator, CanRender Renderer>
class GameLoop {
public:
    explicit GameLoop(DecisionTaker& decisionTaker,
                      PhysicsCalculator& physicsCalculator, Renderer& renderer) :
            m_decisionTaker{decisionTaker},
            m_physicsCalculator{physicsCalculator},
            m_renderer{renderer} {}

    template<CanExitGame GameExiter>
    void run(GameExiter& gameExiter) {
        while (!gameExiter.shouldExitGame()) {
            m_decisionTaker.takeDecisions();
            m_physicsCalculator.computePhysics();
            m_renderer.render();
        }
    }

private:
    DecisionTaker& m_decisionTaker;
    PhysicsCalculator& m_physicsCalculator;
    Renderer& m_renderer;
};

#endif

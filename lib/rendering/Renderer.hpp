#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <concepts>

template<typename T>
concept CanRenderGraphics = requires(T type) {
                                { type.renderGraphics() } -> std::same_as<void>;
                            };

template<CanRenderGraphics GraphicsRenderer>
class Renderer {
public:
    explicit Renderer(GraphicsRenderer& graphicsRenderer) :
            m_graphicsRenderer{graphicsRenderer} {}

    void render() { m_graphicsRenderer.renderGraphics(); }

private:
    GraphicsRenderer& m_graphicsRenderer;
};

#endif

#ifndef ARCHETYPE_HPP
#define ARCHETYPE_HPP

#include <concepts>
#include <span>
#include <tuple>
#include <vector>

template<typename T>
concept Component = std::destructible<T>;

template<typename T, typename... C>
concept ContainedIn = (std::same_as<T, C> || ...);

template<Component... Components>
class Archetype {
public:
    void addEntity(Components... components) {
        auto vvv = [this](auto component) {
            std::get<std::vector<decltype(component)>>(m_components)
                .emplace_back(component);
        };
        ((vvv(components)), ...);
    }

    template<Component RequestedComponent>
        requires(ContainedIn<RequestedComponent, Components...>)
    std::span<RequestedComponent> getComponentSpan() {
        return std::get<std::vector<RequestedComponent>>(m_components);
    }

private:
    std::tuple<std::vector<Components>...> m_components{};
};

#endif

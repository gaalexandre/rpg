#ifndef ARCHETYPE_HPP
#define ARCHETYPE_HPP

#include "EntityId.h"
#include <algorithm>
#include <concepts>
#include <span>
#include <tuple>
#include <vector>

template<typename T>
concept Component = std::move_constructible<T>;

template<typename T, typename... C>
concept ContainedIn = (std::same_as<T, C> || ...);

template<Component... Components>
class Archetype {
public:
    void addEntity(EntityId entityId, Components... components) {
        auto addComponent = [this](auto component) {
            std::get<std::vector<decltype(component)>>(m_components)
                .emplace_back(component);
        };
        ((addComponent(components)), ...);
        m_entityIds.push_back(entityId);
    }

    template<Component RequestedComponent>
        requires(ContainedIn<RequestedComponent, Components...>)
    [[nodiscard]] std::span<RequestedComponent> getComponentSpan() {
        return std::get<std::vector<RequestedComponent>>(m_components);
    }

    template<Component RequestedComponent>
        requires(ContainedIn<RequestedComponent, Components...>)
    [[nodiscard]] std::span<const RequestedComponent> getComponentSpan() const {
        return std::get<std::vector<RequestedComponent>>(m_components);
    }

private:
    std::tuple<std::vector<Components>...> m_components{};
    std::vector<EntityId> m_entityIds{};
};

#endif

#ifndef ENTITYID_H
#define ENTITYID_H

#include <cstddef>
#include <type_traits>

class EntityId {
public:
    EntityId();
    friend bool operator==(const EntityId&, const EntityId&) = default;

private:
    std::size_t m_id;
};

#endif

#include "EntityId.h"

namespace {
std::size_t getNextId() {
    static std::size_t nextId = 0;
    return nextId++;
}
}

EntityId::EntityId() : m_id{getNextId()} {}

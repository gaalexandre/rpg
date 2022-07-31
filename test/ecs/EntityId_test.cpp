#include "EntityId_test.h"
#include "EntityId.h"
#include <algorithm>
#include <boost/ut.hpp>

void testEntityId() {
    using namespace boost::ut;

    "Test EntityId creation"_test = [](std::size_t nbElements) {
        std::vector<EntityId> ids(nbElements);
        expect(std::ranges::all_of(ids, [&ids](EntityId entityId) {
            return std::ranges::count(ids, entityId) == 1;
        })) << "EntityId duplicated";
    } | std::array{0, 1, 15};
}

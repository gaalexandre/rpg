#include "Archetype_test.h"
#include "Archetype.hpp"
#include <algorithm>
#include <boost/ut.hpp>
#include <range/v3/all.hpp>

void testArchetype() {
    using namespace boost::ut;

    "Test addEntity"_test =
        [](const std::vector<std::tuple<int, double>>& values) {
            Archetype<int, double> archetype;
            for (auto [intComponent, doubleComponent] : values) {
                archetype.addEntity(intComponent, doubleComponent);
            }
            auto view1 = ranges::views::zip_with(
                [](int first, double second) {
                    return std::make_tuple(first, second);
                },
                archetype.getComponentSpan<int>(),
                archetype.getComponentSpan<double>());
            auto view2 = ranges::views::all(values);
            expect(ranges::equal(view1, view2))
                << "Entity not added correctly.";
        }
        | std::vector<std::vector<std::tuple<int, double>>>{
            {}, {{1, 10.}}, {{1, 2.}, {1, 0.}, {-1022, 5343.}, {-565466, -2.}}};
}

#include "SimpleSparseSet_test.h"
#include "SimpleSparseSet.hpp"
#include <algorithm>
#include <boost/ut.hpp>
#include <ranges>

void testSimpleSparseSet() {
    using namespace boost::ut;

    "Constructor and iterators"_test =
        [](const std::vector<std::pair<int, double>>& initValues) {
            SimpleSparseSet<int, double, 20> sparseSet{initValues};
            expect(std::ranges::equal(
                sparseSet, initValues,
                [](double const& output, std::pair<int, double> const& input) {
                    return output == input.second;
                }));
            expect(std::ranges::equal(
                sparseSet.begin(), sparseSet.end(), initValues.begin(),
                initValues.end(),
                [](double const& output, std::pair<int, double> const& input) {
                    return output == input.second;
                }));
            expect(std::ranges::equal(
                sparseSet.keyBegin(), sparseSet.keyEnd(), initValues.begin(),
                initValues.end(),
                [](int const& output, std::pair<int, double> const& input) {
                    return output == input.first;
                }));
            expect(std::ranges::equal(
                sparseSet.cbegin(), sparseSet.cend(), initValues.cbegin(),
                initValues.cend(),
                [](double const& output, std::pair<int, double> const& input) {
                    return output == input.second;
                }));
            expect(std::ranges::equal(
                sparseSet.keyCbegin(), sparseSet.keyCend(), initValues.cbegin(),
                initValues.cend(),
                [](int const& output, std::pair<int, double> const& input) {
                    return output == input.first;
                }));
        }
        | std::vector<std::vector<std::pair<int, double>>>{
            {}, {{1, 2.}}, {{1, -21.546}, {0, 0.546}, {15, 21.546}}};

    SimpleSparseSet<int, double, 5> sparseSet{{3, 5.}, {0, 6.}};

    "Contain"_test = [&sparseSet]() {
        expect(sparseSet.contain(0));
        expect(sparseSet.contain(3));
    };

    "Don't contain"_test = [&sparseSet]() {
        expect(!sparseSet.contain(1));
        expect(aborts([&sparseSet]() { return sparseSet.contain(15); }));
    };

    "try_emplace"_test = [sparseSet]() mutable {
        expect(sparseSet.find(1) == sparseSet.cend());
        expect(sparseSet.try_emplace(1, 1.));
        expect(!sparseSet.try_emplace(1, 5.));
        expect(*sparseSet.find(1) == 1._d);
        expect(aborts([&sparseSet]() { return sparseSet.try_emplace(15); }));
    };

    "erase"_test = [sparseSet]() mutable {
        expect(*sparseSet.find(3) == 5._d);
        expect(sparseSet.erase(3));
        expect(!sparseSet.erase(3));
        expect(sparseSet.find(3) == sparseSet.cend());
        expect(aborts([&sparseSet]() { return sparseSet.erase(15); }));
    };

    "find"_test = [sparseSet]() mutable {
        expect(*sparseSet.find(3) == 5._d);
        expect(aborts([&sparseSet]() { return sparseSet.find(15); }));
        expect(sparseSet.find(2) == sparseSet.cend());
        *sparseSet.find(3) = 65.;
        expect(*sparseSet.find(3) == 65._d);
    };
}

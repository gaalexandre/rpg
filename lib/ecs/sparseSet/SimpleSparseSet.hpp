#ifndef SPARSESET_HPP
#define SPARSESET_HPP

#include <array>
#include <cassert>
#include <concepts>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

template<typename T>
concept SparseSetKey = std::regular<T> && std::convertible_to<T, std::size_t>;

template<typename T>
concept SparseSetValue = std::movable<T>;

template<SparseSetKey Key, SparseSetValue Value, std::size_t MaxSize>
class SimpleSparseSet;

template<typename R, typename Key, typename Value, std::size_t MaxSize>
concept InputRangeForSparseSet =
    SparseSetKey<Key> && SparseSetValue<Value> && std::ranges::input_range<R>
    && std::convertible_to<std::ranges::range_value_t<R>, std::pair<Key, Value>>
    && !(std::convertible_to<R, SimpleSparseSet<Key, Value, MaxSize>>);

template<SparseSetKey Key, SparseSetValue Value, std::size_t MaxSize>
class SimpleSparseSet {
public:
    SimpleSparseSet() = default;

    explicit SimpleSparseSet(
        InputRangeForSparseSet<Key, Value, MaxSize> auto inputRange) {
        for (auto& [key, value] : inputRange) {
            try_emplace(key, std::move(value));
        }
    }

    SimpleSparseSet(std::initializer_list<std::pair<Key, Value>> values) {
        for (auto& [key, value] : values) {
            try_emplace(key, std::move(value));
        }
    }

    [[nodiscard]] constexpr bool contain(Key key) const {
        assert(sparseArrayIndex(key) < MaxSize);
        const std::size_t index{m_sparseArray.at(sparseArrayIndex(key))};
        return index < m_packedArray.size() && m_packedArray.at(index) == key;
    }

    [[nodiscard]] constexpr auto begin() { return m_valueArray.begin(); }

    [[nodiscard]] constexpr auto end() { return m_valueArray.end(); }

    [[nodiscard]] constexpr auto cbegin() const {
        return m_valueArray.cbegin();
    }

    [[nodiscard]] constexpr auto cend() const { return m_valueArray.cend(); }

    [[nodiscard]] constexpr auto keyBegin() { return m_packedArray.begin(); }

    [[nodiscard]] constexpr auto keyEnd() { return m_packedArray.end(); }

    [[nodiscard]] constexpr auto keyCbegin() const {
        return m_packedArray.cbegin();
    }

    [[nodiscard]] constexpr auto keyCend() const {
        return m_packedArray.cend();
    }

    template<typename... Args>
    constexpr bool try_emplace(const Key& key, Args&&... args)
        requires(std::constructible_from<Value, Args...>)
    {
        if (contain(key)) {
            return false;
        }
        m_sparseArray.at(sparseArrayIndex(key)) = m_packedArray.size();
        m_packedArray.push_back(key);
        m_valueArray.emplace_back(std::forward<Args>(args)...);
        return true;
    }

    [[nodiscard]] constexpr auto find(const Key& key) {
        if (!contain(key)) {
            return end();
        }
        return begin()
             + static_cast<int>(m_sparseArray.at(sparseArrayIndex(key)));
    }

    [[nodiscard]] constexpr auto find(const Key& key) const {
        if (!contain(key)) {
            return cend();
        }
        return cbegin()
             + static_cast<int>(m_sparseArray.at(sparseArrayIndex(key)));
    }

    constexpr bool erase(const Key& key) {
        if (contain(key)) {
            const std::size_t valueIndex{m_sparseArray.at(sparseArrayIndex(key))};
            std::swap(m_packedArray.at(valueIndex), *m_packedArray.rbegin());
            m_packedArray.pop_back();
            std::swap(m_valueArray.at(valueIndex), *m_valueArray.rbegin());
            m_valueArray.pop_back();
            m_sparseArray.at(sparseArrayIndex(m_packedArray.at(valueIndex))) =
                valueIndex;
            return true;
        }
        return false;
    }

private:
    [[nodiscard]] constexpr std::size_t sparseArrayIndex(Key key) const {
        return static_cast<std::size_t>(key);
    }

    std::array<std::size_t, MaxSize> m_sparseArray{};
    std::vector<Key> m_packedArray{};
    std::vector<Value> m_valueArray{};
};

static_assert(std::ranges::contiguous_range<SimpleSparseSet<int, int, 1>>);
static_assert(std::ranges::sized_range<SimpleSparseSet<int, int, 1>>);

#endif

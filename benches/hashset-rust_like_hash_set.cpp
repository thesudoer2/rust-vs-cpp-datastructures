#include "absl/container/flat_hash_set.h"
#include "absl/container/node_hash_set.h"

#include "absl/container/flat_hash_map.h"

#include <unordered_set>
#include <iostream>
#include <cstdint>
#include <ranges>
#include <utility> // std::monostate

#include <unordered_map>
#include <initializer_list>
#include <iostream>

template <typename T, typename Hash = std::hash<T>, typename Eq = std::equal_to<T>>
class RustLikeHashSet {
private:
    std::unordered_map<T, std::monostate, Hash, Eq> map;
    // absl::flat_hash_map<T, std::monostate> map;

public:
    RustLikeHashSet() = default;

    RustLikeHashSet(std::initializer_list<T> init) {
        for (const auto& item : init) {
            map[item] = std::monostate{};
        }
    }

    bool insert(const T& value) {
        auto [it, inserted] = map.emplace(value, std::monostate{});
        return inserted;
    }

    bool contains(const T& value) const {
        return map.find(value) != map.end();
    }

    bool erase(const T& value) {
        return map.erase(value) > 0;
    }

    size_t size() const {
        return map.size();
    }

    bool empty() const {
        return map.empty();
    }

    void clear() {
        map.clear();
    }

    auto begin() const { return map.begin(); }
    auto end()   const { return map.end(); }

    void debug_print() const {
        for (const auto& [key, _] : map) {
            std::cout << key << " ";
        }
        std::cout << "\n";
    }
};

struct MyRand {
    uint64_t seed = 0;

    uint64_t next() {
        seed = seed * 123456789 + 101112131415;
        return seed;
    }
};

int main() {
    MyRand rand{};
    RustLikeHashSet<std::uint64_t> hashset;
    for (int _: std::views::iota(0, 1'000'000)) {
        hashset.insert(rand.next());
    }
    std::cout << hashset.size() << std::endl;
}

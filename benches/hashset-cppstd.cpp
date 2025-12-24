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

struct MyRand {
    uint64_t seed = 0;

    uint64_t next() {
        seed = seed * 123456789 + 101112131415;
        return seed;
    }
};

int main() {
    MyRand rand{};
    // std::unordered_set<std::uint64_t> hashset;
    std::unordered_set<std::uint64_t, absl::Hash<std::uint64_t>> hashset(20'000'000);
    // for (int _ : std::views::iota(0, 1'000'000)) {
    for (int i {}; i < 10'000'000; ++i) {
        hashset.insert(rand.next());
    }
    std::cout << hashset.size() << std::endl;
}

#include <cstdint>
#include <iostream>
#include <ranges>
#include <utility>

#include <initializer_list>
#include <iostream>

#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>
#include <absl/container/node_hash_set.h>

struct MyRand {
  uint64_t seed = 0;

  __attribute__((always_inline)) inline uint64_t next() {
    seed = seed * 123456789 + 101112131415;
    return seed;
  }
};

int main() {
  MyRand rand{};
  absl::flat_hash_set<std::uint64_t> hashset(20'000'000);

  std::uint64_t t;
  for (int _ : std::views::iota(0, 10'000'000)) {
    t = rand.next();
    hashset.lazy_emplace(t, [t](const auto &ctor) { ctor(t); });
  }

  std::cout << hashset.size() << std::endl;
}

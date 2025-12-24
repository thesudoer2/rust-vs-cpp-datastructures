#include <ankerl/unordered_dense.h>
#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <ranges>
#include <vector>

struct Key32 {
  std::array<uint8_t, 32> data;
  bool operator==(const Key32 &other) const { return data == other.data; }
};

// Use ankerl's wyhash directly
struct WyhashHasher {
  using is_avalanching = void;

  [[nodiscard]] auto operator()(const Key32 &k) const noexcept -> uint64_t {
    return ankerl::unordered_dense::detail::wyhash::hash(k.data.data(), 32);
  }
};

struct MyRand {
  uint64_t seed = 0;

  __attribute__((always_inline)) inline uint64_t next() {
    seed = seed * 123456789 + 101112131415;
    return seed;
  }

  __attribute__((always_inline)) inline Key32 next_key() {
    Key32 key;
    // Fill the 32-byte key with random data (4 x 8 bytes)
    for (size_t i = 0; i < 4; ++i) {
      uint64_t val = next();
      std::memcpy(&key.data[i * 8], &val, sizeof(uint64_t));
    }
    return key;
  }
};

int main() {
  MyRand rand{};

  // Use the custom wyhash hasher
  ankerl::unordered_dense::set<Key32, WyhashHasher> hashset;
  hashset.reserve(20'000'000);

  // Store keys for later lookup
  std::vector<Key32> keys;
  keys.reserve(10'000'000);

  // Insert phase
  for (int _ : std::views::iota(0, 1'000'000)) {
    Key32 key = rand.next_key();
    keys.push_back(key);
    hashset.insert(key);
  }

  std::cout << "Inserted: " << hashset.size() << std::endl;

  // Search phase - lookup all inserted keys
  size_t found = 0;
  for (const auto &key : keys) {
    if (hashset.find(key) != hashset.end()) {
      found++;
    }
  }

  std::cout << "Found: " << found << std::endl;
}
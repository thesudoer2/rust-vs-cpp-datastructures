#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <ranges>
#include <rte_eal.h>
#include <rte_errno.h>
#include <rte_hash.h>
#include <vector>

struct Key32 {
  std::array<uint8_t, 32> data;
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

int main(int argc, char **argv) {
  // Initialize DPDK EAL with hugepages
  const char *eal_argv[] = {"benchmark", "-l", "0", "--"};
  int eal_argc = 4;

  int ret = rte_eal_init(eal_argc, const_cast<char **>(eal_argv));
  if (ret < 0) {
    std::cerr << "Failed to initialize EAL: " << rte_strerror(rte_errno)
              << std::endl;
    return -1;
  }

  // Configure hash table parameters for 32-byte keys
  struct rte_hash_parameters hash_params = {
      .name = "test_hash",
      .entries = 20'000'000,
      .reserved = 0,
      .key_len = sizeof(Key32), // 32 bytes
      .hash_func = nullptr,     // Use default hash function
      .hash_func_init_val = 0,
      .socket_id = static_cast<int>(rte_socket_id()),
      .extra_flag = RTE_HASH_EXTRA_FLAGS_RW_CONCURRENCY_LF};

  // Create hash table
  struct rte_hash *hash = rte_hash_create(&hash_params);
  if (hash == nullptr) {
    std::cerr << "Failed to create hash table: " << rte_strerror(rte_errno)
              << std::endl;
    rte_eal_cleanup();
    return -1;
  }

  MyRand rand{};
  uint8_t dummy_data = 1; // DPDK hash requires data to store

  // Store keys for later lookup
  std::vector<Key32> keys;
  keys.reserve(10'000'000);

  // Insert phase
  for (int _ : std::views::iota(0, 1'000'000)) {
    Key32 key = rand.next_key();
    keys.push_back(key);
    // Add key to hash (rte_hash_add_key_data returns position or error)
    rte_hash_add_key_data(hash, &key, &dummy_data);
  }

  std::cout << "Inserted: " << rte_hash_count(hash) << std::endl;

  // Search phase - lookup all inserted keys
  size_t found = 0;
  for (const auto &key : keys) {
    int32_t ret = rte_hash_lookup(hash, &key);
    if (ret >= 0) { // ret >= 0 means key was found
      found++;
    }
  }

  std::cout << "Found: " << found << std::endl;

  // Cleanup
  rte_hash_free(hash);
  rte_eal_cleanup();

  return 0;
}
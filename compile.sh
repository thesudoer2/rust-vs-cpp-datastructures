CXX_LINK_OPTIONS="-labsl_raw_hash_set -labsl_hashtablez_sampler -labsl_city -labsl_hash -labsl_malloc_internal -labsl_throw_delegate"

mkdir -p bin
clang++-20 benches/$1.cpp -std=c++26 -O3 $CXX_LINK_OPTIONS -o bin/cpp-$1
rustc benches/$1.rs -O -o bin/rust-$1

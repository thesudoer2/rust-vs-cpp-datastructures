#!/usr/bin/bash

CXX_LINK_OPTIONS="-labsl_raw_hash_set -labsl_hashtablez_sampler -labsl_city -labsl_hash -labsl_malloc_internal -labsl_throw_delegate"

mkdir -p bin

for target in $(ls benches/*$1*)
do
    full_filename="${target##*/}"
    extension="${full_filename##*.}"
    pure_filename="${full_filename%%\.$extension}"

    if [ "$extension" == "cpp" ]
    then
        clang++-20 benches/${pure_filename}.cpp -std=c++26 -O3 $CXX_LINK_OPTIONS -o bin/cpp-${pure_filename}
    elif [ "$extension" == "rs" ]
    then
        rustc benches/${pure_filename}.rs -O -o bin/rust-${pure_filename}
    fi
done

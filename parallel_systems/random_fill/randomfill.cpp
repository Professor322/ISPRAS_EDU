//
// Created by kolek on 11.12.2021.
//

#include <cstdint>
#include <cstddef>


/*
 *
 * x_n = x_n-1 * a + c
 * some of the main loop optimizations are finding invariants and unrolling
 * this formula has cross iteration data dependency that's why we can not vectorize it
 * i could not find any invariants
 *
 * we can try to rewrite this formula minimizing dependecies between iterations:
 * x_n = x * a^n + c * (a^0 + ... + a^n-1)
 * we can use this formula to divide our main sequence into the chunks of size j:
 * ex:
 * x_{i + j} = x * a^j + c * (a^0 + ... + a^j - 1)
 * x = x_{i + j}
 * i += j
 * x_{i + j} = x * a^j + c + (a^0 + ... + a^j - 1)
 * ....
 * we need to precalculate prefix powers of (a) and prefix sums of (c * a^i)
 *
 * the rest of an array is calculated scalar way
*/
void randomfill(uint64_t *out, size_t n, uint64_t x, uint64_t a, uint64_t c) {

    const size_t chunk_size = 32;
    uint64_t prefix_pow_a[chunk_size];
    uint64_t prefix_sums[chunk_size];

    prefix_pow_a[0] = a;
    for (size_t i = 1; i < chunk_size; ++i) {
        prefix_pow_a[i] = prefix_pow_a[i - 1] * a;
    }

    prefix_sums[0] = c;
    for (size_t i = 1; i < chunk_size; ++i) {
        prefix_sums[i] = prefix_sums[i - 1] + c * prefix_pow_a[i - 1];
    }

    const size_t chunks_count = n / chunk_size;
    const size_t limit = chunk_size * chunks_count;


    for (size_t i = 0; i < limit; ) {
        for (size_t j = 0; j < chunk_size; ++j) {
            out[i + j] = x * prefix_pow_a[j] + prefix_sums[j];
        }
        i += chunk_size;
        x = out[i - 1];

    }

    for (size_t i = limit; i < n; ++i) {
        x = x * a + c;
        out[i] = x;
    }
}

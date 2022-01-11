#include <cstdint>
#include <cstring>


using word_t = uint32_t;
using byte_t = unsigned char;
using cstr_t = const char*;

constexpr byte_t ascii_digits_begin = 0x30;
constexpr byte_t ascii_letters_begin = 0x61;

inline char get_digit_represenation(byte_t x)
{
    return x <= 9 ? ascii_digits_begin + x : ascii_letters_begin + x - 10;
}

#define WRITE_OUT(out, in, i, iter) \
    byte_t quot_##iter = in[i + iter] / 16; \
    byte_t rem_##iter = in[i + iter] % 16; \
    word_t out_word_##iter = 0x0000785c; \
    out_word_##iter |= get_digit_represenation(quot_##iter) << 16; \
    out_word_##iter |= get_digit_represenation(rem_##iter) << 24; \
    memcpy(out + sizeof(word_t) * iter, &out_word_##iter, sizeof(word_t)); \

void hexdump(char* out, const byte_t* in, size_t n)
{
    if (!n) return;

    constexpr size_t unroll_factor = 8;

    for (size_t i = 0; i < n - unroll_factor; i += unroll_factor, out += unroll_factor * sizeof(word_t))
    {
        WRITE_OUT(out, in, i, 0); 
        WRITE_OUT(out, in, i, 1); 
        WRITE_OUT(out, in, i, 2); 
        WRITE_OUT(out, in, i, 3);
        WRITE_OUT(out, in, i, 4);
        WRITE_OUT(out, in, i, 5);
        WRITE_OUT(out, in, i, 6);
        WRITE_OUT(out, in, i, 7); 
        
    }
    
    for (size_t i = (n / unroll_factor) * unroll_factor; i < n; ++i, out += sizeof(word_t))
    {
        WRITE_OUT(out, in, i, 0);
    }
}


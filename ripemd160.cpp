#define _CRT_SECURE_NO_WARNINGS
#include "ripemd160.h"

void ripemd160(const uint8_t* msg, uint32_t msg_len, uint8_t* hash)
{
    uint32_t i;
    int j;
    uint32_t digest[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0UL };

    for (i = 0; i < (msg_len >> 6); ++i) {
        uint32_t chunk[16];

        for (j = 0; j < 16; ++j) {
            chunk[j] = (uint32_t)(*(msg++));
            chunk[j] |= (uint32_t)(*(msg++)) << 8;
            chunk[j] |= (uint32_t)(*(msg++)) << 16;
            chunk[j] |= (uint32_t)(*(msg++)) << 24;
        }

        compress(digest, chunk);
    }

    // Last chunk
    {
        uint32_t chunk[16] = { 0 };

        for (i = 0; i < (msg_len & 63); ++i) {
            chunk[i >> 2] ^= (uint32_t)*msg++ << ((i & 3) << 3);
        }

        chunk[(msg_len >> 2) & 15] ^= (uint32_t)1 << (8 * (msg_len & 3) + 7);

        if ((msg_len & 63) > 55) {
            compress(digest, chunk);
            memset(chunk, 0, 64);
        }

        chunk[14] = msg_len << 3;
        chunk[15] = (msg_len >> 29);
        compress(digest, chunk);
    }

    for (i = 0; i < 5; ++i) {
        *(hash++) = digest[i];
        *(hash++) = digest[i] >> 8;
        *(hash++) = digest[i] >> 16;
        *(hash++) = digest[i] >> 24;
    }
}
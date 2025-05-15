#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

// SHA-256 Constants: representing the first 32 bits of the fractional parts of the 
// cube roots of the first 64 primes (2 through 311)
static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Initial hash values (first 32 bits of the fractional parts of the square roots of the first 8 primes)
static const uint32_t initial_hash[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// SHA-256 helper functions
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define CH(x, y, z) (((x) & (y)) ^ ((~x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define EP1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))

// Transform a single 512-bit block
static void sha256_transform(SHA256_CTX *ctx, const unsigned char *data) {
    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];

    // Prepare the message schedule (expand the block into 64 32-bit words)
    for (i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    
    // Extend the first 16 words into the remaining 48 words
    for (i = 16; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    // Initialize working variables with current hash value
    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    f = ctx->state[5];
    g = ctx->state[6];
    h = ctx->state[7];

    // Compression function main loop
    for (i = 0; i < 64; ++i) {
        t1 = h + EP1(e) + CH(e, f, g) + K[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    // Add the compressed chunk to the current hash value
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
    ctx->state[5] += f;
    ctx->state[6] += g;
    ctx->state[7] += h;
}

// Initialize SHA-256 context
void sha256_init(SHA256_CTX *ctx) {
    // Copy initial hash values to context state
    memcpy(ctx->state, initial_hash, 32);
    ctx->count[0] = ctx->count[1] = 0;
    memset(ctx->buffer, 0, 64);
}

// Update SHA-256 context with input data
void sha256_update(SHA256_CTX *ctx, const unsigned char *data, size_t len) {
    size_t i, idx;
    
    // Compute number of bytes mod 64
    idx = (size_t)((ctx->count[0] >> 3) & 0x3F);

    // Update bit count (64-bit counter)
    if ((ctx->count[0] += ((uint32_t)len << 3)) < ((uint32_t)len << 3))
        ctx->count[1]++;
    ctx->count[1] += ((uint32_t)len >> 29);

    // Process input data in 64-byte chunks
    for (i = 0; i < len; ++i) {
        ctx->buffer[idx++] = data[i];
        
        // If buffer is full, transform it
        if (idx == 64) {
            sha256_transform(ctx, ctx->buffer);
            idx = 0;
        }
    }
}

// Finalize SHA-256 operation and output the hash
void sha256_final(SHA256_CTX *ctx, unsigned char hash[32]) {
    unsigned char finalcount[8];
    unsigned int i;

    // Convert counter to bytes
    for (i = 0; i < 8; i++)
        finalcount[i] = (unsigned char)((ctx->count[(i >= 4 ? 0 : 1)] >> ((3 - (i & 3)) * 8)) & 255);

    // Pad with a '1' bit followed by zeros
    unsigned char c = 0x80;
    sha256_update(ctx, &c, 1);

    // Pad with zeros until length is 56 mod 64
    while ((ctx->count[0] & 504) != 448) {
        c = 0;
        sha256_update(ctx, &c, 1);
    }

    // Append length (in bits) as a 64-bit big-endian integer
    sha256_update(ctx, finalcount, 8);

    // Store hash value as bytes
    for (i = 0; i < 32; i++)
        hash[i] = (unsigned char)((ctx->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
}

// One-pass SHA-256 function
void sha256(const unsigned char *data, size_t len, unsigned char hash[32]) {
    SHA256_CTX ctx;
    
    sha256_init(&ctx);
    sha256_update(&ctx, data, len);
    sha256_final(&ctx, hash);
}

// Convert binary hash to hex string
char* sha256_hash_string(const unsigned char *hash, char output[65]) {
    int i;
    
    for (i = 0; i < 32; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    
    output[64] = 0;
    return output;
}

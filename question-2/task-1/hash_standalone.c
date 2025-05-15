# Simple SHA-256 Implementation

# If OpenSSL is not available, use this implementation instead
# Replace hash.c with this file if you're not using OpenSSL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// SHA-256 constants
#define CHUNK_SIZE 64
#define TOTAL 8

// SHA-256 Functions
#define ROTRIGHT(word, bits) (((word) >> (bits)) | ((word) << (32-(bits))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))

// SHA-256 Constants (first 32 bits of the fractional parts of the cube roots of the first 64 primes)
static const unsigned int k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Simple implementation of SHA-256 algorithm
void sha256_string(const char* input, char output[65]) {
    // Initialize hash values (first 32 bits of the fractional parts of the square roots of the first 8 primes)
    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;
    
    // Pre-processing: pad the input
    size_t initial_len = strlen(input);
    size_t padded_len = initial_len + 1; // +1 for the 0x80 byte
    
    // Add padding to make total length a multiple of 64 bytes (512 bits)
    padded_len = ((padded_len + 8 + 63) / 64) * 64;
    
    unsigned char* padded_message = (unsigned char*)calloc(padded_len, 1);
    if (!padded_message) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    // Copy original message
    memcpy(padded_message, input, initial_len);
    
    // Append 0x80 byte (10000000)
    padded_message[initial_len] = 0x80;
    
    // Append original length in bits (big-endian) at the end
    uint64_t bit_len = initial_len * 8;
    padded_message[padded_len - 8] = (bit_len >> 56) & 0xFF;
    padded_message[padded_len - 7] = (bit_len >> 48) & 0xFF;
    padded_message[padded_len - 6] = (bit_len >> 40) & 0xFF;
    padded_message[padded_len - 5] = (bit_len >> 32) & 0xFF;
    padded_message[padded_len - 4] = (bit_len >> 24) & 0xFF;
    padded_message[padded_len - 3] = (bit_len >> 16) & 0xFF;
    padded_message[padded_len - 2] = (bit_len >> 8) & 0xFF;
    padded_message[padded_len - 1] = bit_len & 0xFF;
    
    // Process the message in 64-byte chunks
    for (size_t offset = 0; offset < padded_len; offset += 64) {
        unsigned int w[64];
        
        // Break chunk into sixteen 32-bit big-endian integers
        for (int i = 0; i < 16; i++) {
            w[i] = (padded_message[offset + 4*i] << 24)
                 | (padded_message[offset + 4*i + 1] << 16)
                 | (padded_message[offset + 4*i + 2] << 8)
                 | (padded_message[offset + 4*i + 3]);
        }
        
        // Extend the sixteen 32-bit integers into sixty-four 32-bit integers
        for (int i = 16; i < 64; i++) {
            w[i] = SIG1(w[i-2]) + w[i-7] + SIG0(w[i-15]) + w[i-16];
        }
        
        // Initialize hash value for this chunk
        unsigned int a = h0;
        unsigned int b = h1;
        unsigned int c = h2;
        unsigned int d = h3;
        unsigned int e = h4;
        unsigned int f = h5;
        unsigned int g = h6;
        unsigned int h = h7;
        
        // Main loop
        for (int i = 0; i < 64; i++) {
            unsigned int temp1 = h + EP1(e) + CH(e, f, g) + k[i] + w[i];
            unsigned int temp2 = EP0(a) + MAJ(a, b, c);
            
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
        
        // Add chunk's hash to result
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }
    
    // Free the padded message
    free(padded_message);
    
    // Produce the final hash value (big-endian)
    unsigned int hash[8] = { h0, h1, h2, h3, h4, h5, h6, h7 };
    for (int i = 0; i < 8; i++) {
        sprintf(output + (i * 8), "%08x", hash[i]);
    }
    
    // Ensure null termination
    output[64] = '\0';
}

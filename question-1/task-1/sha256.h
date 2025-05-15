#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stddef.h>

// Define the SHA-256 context structure
typedef struct {
    uint32_t state[8];          // Current state (hash values)
    uint32_t count[2];          // Number of bits processed so far (64-bit counter)
    unsigned char buffer[64];   // Input buffer for processing
} SHA256_CTX;

// Function prototypes
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const unsigned char *data, size_t len);
void sha256_final(SHA256_CTX *ctx, unsigned char hash[32]);
void sha256(const unsigned char *data, size_t len, unsigned char hash[32]);
char* sha256_hash_string(const unsigned char *hash, char output[65]);

#endif // SHA256_H

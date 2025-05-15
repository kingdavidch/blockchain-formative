#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "hash.h"

/**
 * Computes the SHA-256 hash of a string and returns it as a hex string
 * 
 * @param input The input string to hash
 * @param output The buffer to store the resulting hash (must be at least 65 bytes)
 */
void sha256_string(const char* input, char output[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Initialize the SHA-256 context
    SHA256_Init(&sha256);
    
    // Add data to be hashed
    SHA256_Update(&sha256, input, strlen(input));
    
    // Complete the hash computation
    SHA256_Final(hash, &sha256);
    
    // Convert binary hash to hex string
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    
    // Ensure null termination
    output[64] = '\0';
}

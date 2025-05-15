#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"

int main(int argc, char *argv[]) {
    // Default input string
    const char *input = "Blockchain Cryptography";
    
    // Use command line argument if provided
    if (argc > 1) {
        input = argv[1];
    }
    
    printf("Input: \"%s\"\n", input);
    
    // Calculate hash
    unsigned char hash[32];
    char hash_string[65];
    
    // Perform the SHA-256 hashing
    sha256((const unsigned char*)input, strlen(input), hash);
    
    // Convert to hex string
    sha256_hash_string(hash, hash_string);
    
    printf("SHA-256 Hash: %s\n", hash_string);
    
    return 0;
}

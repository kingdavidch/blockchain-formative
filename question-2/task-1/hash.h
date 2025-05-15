#ifndef HASH_H
#define HASH_H

/**
 * Computes the SHA-256 hash of a string and returns it as a hex string
 * 
 * @param input The input string to hash
 * @param output The buffer to store the resulting hash (must be at least 65 bytes)
 */
void sha256_string(const char* input, char output[65]);

#endif // HASH_H

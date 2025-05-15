#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "block.h"
#include "hash.h"

/**
 * Creates a new block with the given parameters
 * 
 * @param index Position in the blockchain
 * @param data Data to store in the block
 * @param prev_hash Hash of the previous block
 * @return Pointer to the newly created block or NULL if allocation failed
 */
Block* create_block(uint32_t index, const char* data, const char* prev_hash) {
    // Allocate memory for new block
    Block* new_block = (Block*)malloc(sizeof(Block));
    if (new_block == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for block\n");
        return NULL;
    }
    
    // Initialize block properties
    new_block->index = index;
    new_block->timestamp = time(NULL);  // Current time
    
    // Copy data into block (safely)
    strncpy(new_block->data, data, MAX_DATA_SIZE - 1);
    new_block->data[MAX_DATA_SIZE - 1] = '\0';  // Ensure null termination
    
    // Copy previous hash (safely)
    strncpy(new_block->prev_hash, prev_hash, HASH_LENGTH);
    new_block->prev_hash[HASH_LENGTH] = '\0';  // Ensure null termination
    
    // Calculate hash for this block
    calculate_hash(new_block);
    
    return new_block;
}

/**
 * Calculates the hash of a block and stores it in the block's hash field
 * 
 * @param block Pointer to the block to hash
 */
void calculate_hash(Block* block) {
    if (block == NULL) {
        return;
    }
    
    // Create a buffer for all data to be hashed
    char buffer[MAX_DATA_SIZE + 256] = {0};
    
    // Combine block components into a single string
    sprintf(buffer, "%u%ld%s%s", 
            block->index, 
            block->timestamp, 
            block->data, 
            block->prev_hash);
    
    // Calculate SHA-256 hash of the buffer
    sha256_string(buffer, block->hash);
}

/**
 * Displays all information contained in a block
 * 
 * @param block Pointer to the block to display
 */
void display_block(const Block* block) {
    if (block == NULL) {
        printf("Block is NULL\n");
        return;
    }
    
    // Format timestamp for display
    char time_str[30];
    struct tm *timeinfo = localtime(&block->timestamp);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    // Print block information
    printf("==================================================\n");
    printf("Block #%u\n", block->index);
    printf("==================================================\n");
    printf("Timestamp: %s\n", time_str);
    printf("Data: %s\n", block->data);
    printf("Previous Hash: %s\n", block->prev_hash);
    printf("Hash: %s\n", block->hash);
    printf("==================================================\n\n");
}

/**
 * Frees memory allocated for a block
 * 
 * @param block Pointer to the block to free
 */
void free_block(Block* block) {
    if (block != NULL) {
        free(block);
    }
}

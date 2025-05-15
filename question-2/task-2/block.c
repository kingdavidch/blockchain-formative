#include "block.h"
#include "sha256.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

Block* create_block(unsigned int index, const char *data, const char *previous_hash) {
    Block *block = (Block*)malloc(sizeof(Block));
    if (!block) return NULL;
    
    block->index = index;
    block->timestamp = time(NULL);
    
    block->data = strdup(data);
    if (!block->data) {
        free(block);
        return NULL;
    }
    
    block->previous_hash = strdup(previous_hash);
    if (!block->previous_hash) {
        free(block->data);
        free(block);
        return NULL;
    }
    
    block->hash = NULL;
    calculate_hash(block);
    
    return block;
}

void destroy_block(Block *block) {
    if (block) {
        free(block->data);
        free(block->previous_hash);
        free(block->hash);
        free(block);
    }
}

void calculate_hash(Block *block) {
    if (block->hash) {
        free(block->hash);
    }
    
    // Create a string representation of the block's data
    char block_data[1024];
    snprintf(block_data, sizeof(block_data), "%u%ld%s%s", 
             block->index, block->timestamp, block->data, block->previous_hash);
    
    // Calculate SHA-256 hash
    block->hash = sha256(block_data);
}

void print_block(const Block *block) {
    printf("Block %u:\n", block->index);
    printf("  Timestamp: %ld\n", block->timestamp);
    printf("  Data: %s\n", block->data);
    printf("  Previous Hash: %s\n", block->previous_hash);
    printf("  Hash: %s\n", block->hash);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blockchain.h"
#include "sha256.h"

// Create a new blockchain with a genesis block
Blockchain* create_blockchain() {
    Blockchain* blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    if (blockchain == NULL) {
        fprintf(stderr, "Failed to allocate memory for blockchain\n");
        return NULL;
    }

    // Initialize blockchain structure
    blockchain->size = 0;
    blockchain->genesis = NULL;
    blockchain->latest = NULL;

    // Create genesis block
    Block* genesis = (Block*)malloc(sizeof(Block));
    if (genesis == NULL) {
        fprintf(stderr, "Failed to allocate memory for genesis block\n");
        free(blockchain);
        return NULL;
    }

    // Initialize genesis block
    genesis->index = 0;
    genesis->timestamp = time(NULL);
    strcpy(genesis->data, "Genesis Block");
    strcpy(genesis->prev_hash, "0000000000000000000000000000000000000000000000000000000000000000");
    genesis->nonce = 0;
    genesis->next = NULL;

    // Calculate genesis block hash
    calculate_block_hash(genesis, genesis->hash);

    // Set genesis as the first and latest block
    blockchain->genesis = genesis;
    blockchain->latest = genesis;
    blockchain->size = 1;

    return blockchain;
}

// Calculate the hash of a block
void calculate_block_hash(Block* block, char hash_str[65]) {
    // Create a buffer to contain all block data for hashing
    char buffer[512] = {0};
    
    // Format block data into a single string for hashing
    sprintf(buffer, "%u%ld%s%s%u", 
            block->index, 
            block->timestamp, 
            block->data, 
            block->prev_hash,
            block->nonce);
    
    // Calculate SHA-256 hash
    unsigned char hash[32];
    sha256((unsigned char*)buffer, strlen(buffer), hash);
    
    // Convert hash to string
    sha256_hash_string(hash, hash_str);
}

// Create a new block and add it to the blockchain
Block* create_new_block(Blockchain* blockchain, const char* data) {
    if (blockchain == NULL || blockchain->latest == NULL) {
        fprintf(stderr, "Invalid blockchain\n");
        return NULL;
    }
    
    // Validate the blockchain before adding a new block
    if (!validate_blockchain(blockchain)) {
        fprintf(stderr, "Cannot add block to invalid blockchain\n");
        return NULL;
    }

    // Create new block
    Block* new_block = (Block*)malloc(sizeof(Block));
    if (new_block == NULL) {
        fprintf(stderr, "Failed to allocate memory for new block\n");
        return NULL;
    }

    // Initialize block with data
    new_block->index = blockchain->latest->index + 1;
    new_block->timestamp = time(NULL);
    strncpy(new_block->data, data, MAX_DATA_SIZE - 1);
    new_block->data[MAX_DATA_SIZE - 1] = '\0'; // Ensure null termination
    strcpy(new_block->prev_hash, blockchain->latest->hash);
    new_block->nonce = 0; // Simple implementation, no mining
    new_block->next = NULL;

    // Calculate the hash for this block
    calculate_block_hash(new_block, new_block->hash);

    // Add block to chain
    blockchain->latest->next = new_block;
    blockchain->latest = new_block;
    blockchain->size++;

    return new_block;
}

// Validate the entire blockchain
int validate_blockchain(Blockchain* blockchain) {
    if (blockchain == NULL || blockchain->genesis == NULL) {
        return 0; // Invalid blockchain
    }

    // Start with the genesis block
    Block* current_block = blockchain->genesis;
    Block* next_block;
    char calculated_hash[65];
    
    // Check each block
    while (current_block->next != NULL) {
        next_block = current_block->next;
        
        // Verify the link (previous hash)
        if (strcmp(next_block->prev_hash, current_block->hash) != 0) {
            fprintf(stderr, "Blockchain invalid: Block %u has incorrect previous hash\n", next_block->index);
            return 0;
        }
        
        // Verify current block's hash
        calculate_block_hash(current_block, calculated_hash);
        if (strcmp(calculated_hash, current_block->hash) != 0) {
            fprintf(stderr, "Blockchain invalid: Block %u has incorrect hash\n", current_block->index);
            return 0;
        }
        
        current_block = next_block;
    }
    
    // Verify the hash of the last block
    calculate_block_hash(current_block, calculated_hash);
    if (strcmp(calculated_hash, current_block->hash) != 0) {
        fprintf(stderr, "Blockchain invalid: Block %u has incorrect hash\n", current_block->index);
        return 0;
    }
    
    return 1; // Blockchain is valid
}

// Print the entire blockchain
void print_blockchain(Blockchain* blockchain) {
    if (blockchain == NULL || blockchain->genesis == NULL) {
        printf("Empty blockchain\n");
        return;
    }

    Block* current = blockchain->genesis;
    
    printf("Blockchain with %u blocks:\n", blockchain->size);
    printf("--------------------------------------------------\n");
    
    while (current != NULL) {
        char time_str[30];
        struct tm *timeinfo;
        timeinfo = localtime(&current->timestamp);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", timeinfo);
        
        printf("Block #%u\n", current->index);
        printf("  Timestamp: %s\n", time_str);
        printf("  Data: %s\n", current->data);
        printf("  Previous Hash: %s\n", current->prev_hash);
        printf("  Hash: %s\n", current->hash);
        printf("--------------------------------------------------\n");
        
        current = current->next;
    }
}

// Free all memory used by the blockchain
void free_blockchain(Blockchain* blockchain) {
    if (blockchain == NULL) {
        return;
    }
    
    Block* current = blockchain->genesis;
    Block* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(blockchain);
}

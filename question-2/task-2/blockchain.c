#include "blockchain.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Blockchain* create_blockchain() {
    Blockchain *blockchain = (Blockchain*)malloc(sizeof(Blockchain));
    if (!blockchain) return NULL;
    
    blockchain->head = NULL;
    blockchain->tail = NULL;
    
    // Create genesis block
    add_block(blockchain, "Genesis Block");
    
    return blockchain;
}

void destroy_blockchain(Blockchain *blockchain) {
    if (!blockchain) return;
    
    BlockchainNode *current = blockchain->head;
    while (current) {
        BlockchainNode *next = current->next;
        destroy_block(current->block);
        free(current);
        current = next;
    }
    
    free(blockchain);
}

void add_block(Blockchain *blockchain, const char *data) {
    if (!blockchain) return;
    
    BlockchainNode *new_node = (BlockchainNode*)malloc(sizeof(BlockchainNode));
    if (!new_node) return;
    
    const char *prev_hash = blockchain->tail ? blockchain->tail->block->hash : "0";
    unsigned int index = blockchain->tail ? blockchain->tail->block->index + 1 : 0;
    
    new_node->block = create_block(index, data, prev_hash);
    new_node->next = NULL;
    
    if (!blockchain->head) {
        blockchain->head = new_node;
    } else {
        blockchain->tail->next = new_node;
    }
    blockchain->tail = new_node;
}

int is_blockchain_valid(const Blockchain *blockchain) {
    if (!blockchain || !blockchain->head) return 0;
    
    BlockchainNode *current = blockchain->head;
    BlockchainNode *next = current->next;
    
    // Check genesis block
    if (current->block->index != 0 || 
        strcmp(current->block->previous_hash, "0") != 0) {
        return 0;
    }
    
    char *calculated_hash = NULL;
    
    while (next) {
        // Check if current block's hash matches next block's previous_hash
        if (strcmp(current->block->hash, next->block->previous_hash) != 0) {
            return 0;
        }
        
        // Verify current block's hash is correct
        char block_data[1024];
        snprintf(block_data, sizeof(block_data), "%u%ld%s%s", 
                 current->block->index, current->block->timestamp, 
                 current->block->data, current->block->previous_hash);
        
        calculated_hash = sha256(block_data);
        if (strcmp(calculated_hash, current->block->hash) != 0) {
            free(calculated_hash);
            return 0;
        }
        free(calculated_hash);
        
        current = next;
        next = current->next;
    }
    
    // Verify last block's hash
    char block_data[1024];
    snprintf(block_data, sizeof(block_data), "%u%ld%s%s", 
             current->block->index, current->block->timestamp, 
             current->block->data, current->block->previous_hash);
    
    calculated_hash = sha256(block_data);
    int result = strcmp(calculated_hash, current->block->hash) == 0;
    free(calculated_hash);
    
    return result;
}

void print_blockchain(const Blockchain *blockchain) {
    if (!blockchain) {
        printf("Blockchain is NULL\n");
        return;
    }
    
    printf("Blockchain:\n");
    printf("===========\n");
    
    BlockchainNode *current = blockchain->head;
    while (current) {
        print_block(current->block);
        current = current->next;
        if (current) printf("\n↓\n\n");
    }
    
    printf("\nBlockchain is %s\n", is_blockchain_valid(blockchain) ? "valid" : "invalid");
}

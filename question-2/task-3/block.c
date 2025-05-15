#include "block.h"
#include "sha256.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

Block* create_block(unsigned int index, const char *previous_hash) {
    Block *block = (Block*)malloc(sizeof(Block));
    if (!block) return NULL;
    
    block->index = index;
    block->timestamp = time(NULL);
    block->transaction_count = 0;
    block->transactions = NULL;
    
    block->previous_hash = strdup(previous_hash);
    if (!block->previous_hash) {
        free(block);
        return NULL;
    }
    
    block->hash = NULL;
    calculate_hash(block);
    
    return block;
}

void destroy_block(Block *block) {
    if (block) {
        free(block->previous_hash);
        free(block->hash);
        
        for (unsigned int i = 0; i < block->transaction_count; i++) {
            destroy_transaction(block->transactions[i]);
        }
        free(block->transactions);
        
        free(block);
    }
}

void calculate_hash(Block *block) {
    if (block->hash) {
        free(block->hash);
    }
    
    // Create a string representation of the block's data
    char block_data[4096]; // Increased size for transactions
    char *ptr = block_data;
    
    // Start with basic block info
    ptr += snprintf(ptr, sizeof(block_data), "%u%ld", 
                   block->index, block->timestamp);
    
    // Add all transactions
    for (unsigned int i = 0; i < block->transaction_count; i++) {
        char *tx_str = transaction_to_string(block->transactions[i]);
        if (tx_str) {
            ptr += snprintf(ptr, sizeof(block_data) - (ptr - block_data), "%s", tx_str);
            free(tx_str);
        }
    }
    
    // Add previous hash
    snprintf(ptr, sizeof(block_data) - (ptr - block_data), "%s", block->previous_hash);
    
    // Calculate SHA-256 hash
    block->hash = sha256(block_data);
}

void print_block(const Block *block) {
    printf("Block %u:\n", block->index);
    printf("  Timestamp: %ld\n", block->timestamp);
    printf("  Previous Hash: %s\n", block->previous_hash);
    printf("  Hash: %s\n", block->hash);
    printf("  Transactions (%u):\n", block->transaction_count);
    
    for (unsigned int i = 0; i < block->transaction_count; i++) {
        printf("    ");
        print_transaction(block->transactions[i]);
        if (i < block->transaction_count - 1) printf("\n");
    }
}

int add_transaction_to_block(Block *block, Transaction *transaction) {
    if (!block || !transaction) return 0;
    
    Transaction **new_transactions = realloc(block->transactions, 
                                          (block->transaction_count + 1) * sizeof(Transaction*));
    if (!new_transactions) return 0;
    
    block->transactions = new_transactions;
    block->transactions[block->transaction_count] = transaction;
    block->transaction_count++;
    
    // Recalculate hash since transactions changed
    calculate_hash(block);
    
    return 1;
}

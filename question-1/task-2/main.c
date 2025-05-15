#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

int main() {
    printf("Creating a simple blockchain simulation...\n\n");
    
    // Create a new blockchain (includes genesis block)
    Blockchain* blockchain = create_blockchain();
    if (blockchain == NULL) {
        fprintf(stderr, "Failed to create blockchain\n");
        return 1;
    }
    
    // Print the genesis block
    printf("Initial blockchain with genesis block:\n");
    print_blockchain(blockchain);
    
    // Add some blocks to the chain
    printf("\nAdding Block 1 with transaction data...\n");
    create_new_block(blockchain, "Alice sent 5 BTC to Bob");
    
    printf("\nAdding Block 2 with transaction data...\n");
    create_new_block(blockchain, "Bob sent 3 BTC to Charlie");
    
    printf("\nAdding Block 3 with transaction data...\n");
    create_new_block(blockchain, "Charlie sent 1 BTC to David");
    
    // Print the full blockchain
    printf("\nFull blockchain after adding blocks:\n");
    print_blockchain(blockchain);
    
    // Validate the blockchain
    printf("\nValidating blockchain integrity...\n");
    if (validate_blockchain(blockchain)) {
        printf("Blockchain validation successful: Chain integrity confirmed\n");
    } else {
        printf("Blockchain validation failed: Chain integrity compromised\n");
    }
    
    // Optional: Demonstrate tampering
    printf("\nDemonstrating blockchain tamper detection...\n");
    printf("Attempting to modify data in Block #2...\n");
    
    // Find block #2
    Block* block = blockchain->genesis->next;
    if (block != NULL) {
        // Modify the data (this should break the chain integrity)
        strcpy(block->data, "Bob sent 300 BTC to Charlie");
        printf("Data modified to: %s\n", block->data);
        
        // Validation should now fail
        printf("\nValidating blockchain after tampering...\n");
        if (validate_blockchain(blockchain)) {
            printf("Blockchain validation successful: Chain integrity confirmed\n");
        } else {
            printf("Blockchain validation failed: Chain integrity compromised\n");
            printf("This demonstrates how tampered data is detected in a blockchain\n");
        }
    }

    // Free memory
    free_blockchain(blockchain);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block.h"

/**
 * Main function to test block creation and display
 */
int main() {
    printf("Blockchain Block Structure - Test Program\n\n");
    
    // Create a genesis block (first block in the chain)
    printf("Creating Genesis Block...\n");
    Block* genesis = create_block(
        0,                                                          // Index 0
        "Genesis Block - First block in the chain",                 // Data
        "0000000000000000000000000000000000000000000000000000000000000000"  // No previous hash (all zeros)
    );
    
    if (genesis == NULL) {
        fprintf(stderr, "Failed to create genesis block\n");
        return 1;
    }
    
    // Display the genesis block
    printf("Genesis Block created successfully:\n");
    display_block(genesis);
    
    // Create a second block that links to the genesis block
    printf("Creating Block #1...\n");
    Block* block1 = create_block(
        1,                        // Index 1
        "Transaction: Alice sent 5 BTC to Bob",  // Sample transaction data
        genesis->hash             // Previous hash (from genesis)
    );
    
    if (block1 == NULL) {
        fprintf(stderr, "Failed to create block #1\n");
        free_block(genesis);
        return 1;
    }
    
    // Display the second block
    printf("Block #1 created successfully:\n");
    display_block(block1);
    
    // Clean up allocated memory
    free_block(genesis);
    free_block(block1);
    
    printf("Block test completed successfully\n");
    return 0;
}

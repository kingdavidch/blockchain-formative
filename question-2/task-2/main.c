#include "blockchain.h"
#include <stdio.h>

int main() {
    // Create a new blockchain
    Blockchain *blockchain = create_blockchain();
    
    // Add some blocks
    add_block(blockchain, "First Transaction");
    add_block(blockchain, "Second Transaction");
    add_block(blockchain, "Third Transaction");
    
    // Print the blockchain
    print_blockchain(blockchain);
    
    // Validate the blockchain
    if (is_blockchain_valid(blockchain)) {
        printf("\nBlockchain validation successful!\n");
    } else {
        printf("\nBlockchain validation failed!\n");
    }
    
    // Clean up
    destroy_blockchain(blockchain);
    
    return 0;
}

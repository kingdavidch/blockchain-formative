#include "blockchain.h"
#include <stdio.h>

int main() {
    // Create a new blockchain
    Blockchain *blockchain = create_blockchain();
    
    // Create some transactions
    Transaction *tx1 = create_transaction("Alice", "Bob", 1.5);
    Transaction *tx2 = create_transaction("Bob", "Charlie", 0.7);
    Transaction *tx3 = create_transaction("Charlie", "Alice", 2.1);
    Transaction *tx4 = create_transaction("Dave", "Eve", 3.0);
    Transaction *tx5 = create_transaction("Eve", "Alice", 1.2);
    
    // Add transactions to the blockchain
    add_transaction(blockchain, tx1);
    add_transaction(blockchain, tx2);
    add_transaction(blockchain, tx3);
    add_transaction(blockchain, tx4);
    add_transaction(blockchain, tx5);
    
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

#include "transaction.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

Transaction* create_transaction(const char *sender, const char *receiver, double amount) {
    Transaction *tx = (Transaction*)malloc(sizeof(Transaction));
    if (!tx) return NULL;
    
    tx->sender = strdup(sender);
    tx->receiver = strdup(receiver);
    tx->amount = amount;
    tx->timestamp = time(NULL);
    
    if (!tx->sender || !tx->receiver) {
        if (tx->sender) free(tx->sender);
        if (tx->receiver) free(tx->receiver);
        free(tx);
        return NULL;
    }
    
    return tx;
}

void destroy_transaction(Transaction *transaction) {
    if (transaction) {
        free(transaction->sender);
        free(transaction->receiver);
        free(transaction);
    }
}

void print_transaction(const Transaction *transaction) {
    printf("Transaction:\n");
    printf("  From: %s\n", transaction->sender);
    printf("  To: %s\n", transaction->receiver);
    printf("  Amount: %.2f\n", transaction->amount);
    printf("  Timestamp: %ld\n", transaction->timestamp);
}

char* transaction_to_string(const Transaction *transaction) {
    char *str = (char*)malloc(256 * sizeof(char));
    if (!str) return NULL;
    
    snprintf(str, 256, "%s|%s|%.2f|%ld", 
             transaction->sender, 
             transaction->receiver, 
             transaction->amount, 
             transaction->timestamp);
    
    return str;
}

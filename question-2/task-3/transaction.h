#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    char *sender;
    char *receiver;
    double amount;
    time_t timestamp;
} Transaction;

Transaction* create_transaction(const char *sender, const char *receiver, double amount);
void destroy_transaction(Transaction *transaction);
void print_transaction(const Transaction *transaction);
char* transaction_to_string(const Transaction *transaction);

#endif // TRANSACTION_H

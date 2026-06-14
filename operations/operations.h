#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "../types.h"

void deposit(Account* accounts, int n, int user_id);
void withdraw(Account* accounts, int n, int user_id);
void transfer(Account* accounts, int n, int user_id, Transaction* queue, int* qc);
void process_transactions(Account* accounts, int n, Transaction* queue, int* qc);

#endif

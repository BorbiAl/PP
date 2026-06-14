#include "operations.h"
#include <stdio.h>
#include <string.h>

static Account* find_by_user(Account* a, int n, int uid) {
    for (int i = 0; i < n; i++)
        if (a[i].user_id == uid) return &a[i];
    return NULL;
}

static Account* find_by_number(Account* a, int n, const char* num) {
    for (int i = 0; i < n; i++)
        if (strcmp(a[i].number, num) == 0) return &a[i];
    return NULL;
}

void deposit(Account* accounts, int n, int user_id) {
    Account* a = find_by_user(accounts, n, user_id);
    if (!a) { printf("Сметката не е намерена.\n"); return; }
    double amount;
    printf("Сума: ");
    scanf(" %lf", &amount);
    if (amount <= 0) { printf("Невалидна сума.\n"); return; }
    a->balance += amount;
    printf("Депозирано %.2f €. Баланс: %.2f €.\n", amount, a->balance);
}

void withdraw(Account* accounts, int n, int user_id) {
    Account* a = find_by_user(accounts, n, user_id);
    if (!a) { printf("Сметката не е намерена.\n"); return; }
    double amount;
    printf("Сума: ");
    scanf(" %lf", &amount);
    if (amount <= 0) { printf("Невалидна сума.\n"); return; }
    if (amount > a->balance) { printf("Недостатъчен баланс.\n"); return; }
    a->balance -= amount;
    printf("Изтеглено %.2f €. Баланс: %.2f €.\n", amount, a->balance);
}

void transfer(Account* accounts, int n, int user_id, Transaction* queue, int* qc) {
    Account* from = find_by_user(accounts, n, user_id);
    if (!from) { printf("Сметката не е намерена.\n"); return; }
    char to_num[16];
    double amount;
    printf("Целева сметка: ");
    scanf("%15s", to_num);
    printf("Сума: ");
    scanf(" %lf", &amount);
    if (amount <= 0) { printf("Невалидна сума.\n"); return; }
    if (strcmp(from->number, to_num) == 0) { printf("Не може към собствената си сметка.\n"); return; }
    if (!find_by_number(accounts, n, to_num)) { printf("Сметката не съществува.\n"); return; }
    queue[*qc].amount = amount;
    strcpy(queue[*qc].from, from->number);
    strcpy(queue[*qc].to, to_num);
    (*qc)++;
    printf("Транзакцията е добавена.\n");
}

void process_transactions(Account* accounts, int n, Transaction* queue, int* qc) {
    if (*qc == 0) { printf("Няма транзакции.\n"); return; }
    for (int i = 0; i < *qc; i++) {
        Account* from = find_by_number(accounts, n, queue[i].from);
        Account* to = find_by_number(accounts, n, queue[i].to);
        if (!from || !to) { printf("Невалидна транзакция.\n"); continue; }
        if (from->balance < queue[i].amount) {
            printf("Недостатъчен баланс: %s -> %s\n", queue[i].from, queue[i].to);
            continue;
        }
        from->balance -= queue[i].amount;
        to->balance += queue[i].amount;
        printf("Прехвърлено %.2f €.: %s -> %s\n", queue[i].amount, queue[i].from, queue[i].to);
    }
    *qc = 0;
}

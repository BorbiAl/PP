#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "types.h"
#include "auth/auth.h"
#include "operations/operations.h"

User users[MAX];
int uc = 0;
Account accounts[MAX];
int ac = 0;
Transaction queue[MAX];
int qc = 0;

void load_users() {
    FILE* f = fopen("users.txt", "r");
    if (!f) return;
    while (fscanf(f, "%d %49s %lu", &users[uc].id, users[uc].username, &users[uc].pwd_hash) == 3) uc++;
    fclose(f);
}

void save_users() {
    FILE* f = fopen("users.txt", "w");
    if (!f) return;
    for (int i = 0; i < uc; i++)
        fprintf(f, "%d %s %lu\n", users[i].id, users[i].username, users[i].pwd_hash);
    fclose(f);
}

void load_accounts() {
    FILE* f = fopen("accounts.txt", "r");
    if (!f) return;
    while (fscanf(f, "%15s %lf %d", accounts[ac].number, &accounts[ac].balance, &accounts[ac].user_id) == 3) ac++;
    fclose(f);
}

void save_accounts() {
    FILE* f = fopen("accounts.txt", "w");
    if (!f) return;
    for (int i = 0; i < ac; i++)
        fprintf(f, "%s %.2f %d\n", accounts[i].number, accounts[i].balance, accounts[i].user_id);
    fclose(f);
}

void load_transactions() {
    FILE* f = fopen("transactions.txt", "r");
    if (!f) return;
    while (fscanf(f, "%lf %15s %15s", &queue[qc].amount, queue[qc].from, queue[qc].to) == 3) qc++;
    fclose(f);
}

void save_transactions() {
    FILE* f = fopen("transactions.txt", "w");
    if (!f) return;
    for (int i = 0; i < qc; i++)
        fprintf(f, "%.2f %s %s\n", queue[i].amount, queue[i].from, queue[i].to);
    fclose(f);
}

int main() {
    SetConsoleOutputCP(65001);
    srand(time(NULL));
    load_users();
    load_accounts();
    load_transactions();

    int uid = -1, choice;

    while (1) {
        if (uid == -1) {
            printf("\n1. Вход  2. Регистрация  0. Изход\n> ");
            scanf(" %d", &choice);
            if (choice == 0) break;
            if (choice == 1) login_user(users, uc, &uid);
            else if (choice == 2) {
                if (register_user(users, &uc, accounts, &ac)) {
                    save_users();
                    save_accounts();
                }
            }
        } else {
            Account* a = NULL;
            for (int i = 0; i < ac; i++) if (accounts[i].user_id == uid) { a = &accounts[i]; break; }
            printf("\nСметка: %s | Баланс: %.2f €.\n", a->number, a->balance);
            printf("1. Депозит  2. Теглене  3. Трансфер  4. Транзакции  0. Логаут\n> ");
            scanf(" %d", &choice);
            if (choice == 1)      { deposit(accounts, ac, uid); save_accounts(); }
            else if (choice == 2) { withdraw(accounts, ac, uid); save_accounts(); }
            else if (choice == 3) { transfer(accounts, ac, uid, queue, &qc); save_transactions(); }
            else if (choice == 4) { process_transactions(accounts, ac, queue, &qc); save_accounts(); save_transactions(); }
            else if (choice == 0) { uid = -1; printf("Излязохте.\n"); }
        }
    }
    return 0;
}

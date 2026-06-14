#include "auth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long hash_pwd(const char* s) {
    unsigned long h = 5381;
    while (*s) h = h * 33 ^ (unsigned char)*s++;
    return h;
}

static void gen_number(char* buf, Account* accounts, int n) {
    const char c[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int ok;
    do {
        for (int i = 0; i < 10; i++) buf[i] = c[rand() % 36];
        buf[10] = '\0';
        ok = 1;
        for (int i = 0; i < n; i++)
            if (strcmp(accounts[i].number, buf) == 0) { ok = 0; break; }
    } while (!ok);
}

int register_user(User* users, int* uc, Account* accounts, int* ac) {
    char username[50], password[100];
    printf("Потребителско име: ");
    scanf("%49s", username);
    printf("Парола: ");
    scanf("%99s", password);

    for (int i = 0; i < *uc; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Потребителят вече съществува.\n");
            return 0;
        }
    }

    users[*uc].id = *uc + 1;
    strcpy(users[*uc].username, username);
    users[*uc].pwd_hash = hash_pwd(password);
    (*uc)++;

    gen_number(accounts[*ac].number, accounts, *ac);
    accounts[*ac].balance = 0.0;
    accounts[*ac].user_id = users[*uc - 1].id;
    (*ac)++;

    printf("Успешна регистрация! Номер на сметка: %s\n", accounts[*ac - 1].number);
    return 1;
}

int login_user(User* users, int uc, int* out_id) {
    char username[50], password[100];
    printf("Потребителско име: ");
    scanf("%49s", username);
    printf("Парола: ");
    scanf("%99s", password);

    unsigned long h = hash_pwd(password);
    for (int i = 0; i < uc; i++) {
        if (strcmp(users[i].username, username) == 0 && users[i].pwd_hash == h) {
            *out_id = users[i].id;
            printf("Добре дошъл, %s!\n", username);
            return 1;
        }
    }
    printf("Грешно потребителско име или парола.\n");
    return 0;
}

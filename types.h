#ifndef TYPES_H
#define TYPES_H

#define MAX 100

typedef struct {
    int id;
    char username[50];
    unsigned long pwd_hash;
} User;

typedef struct {
    char number[16];
    double balance;
    int user_id;
} Account;

typedef struct {
    double amount;
    char from[16];
    char to[16];
} Transaction;

#endif

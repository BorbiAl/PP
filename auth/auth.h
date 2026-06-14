#ifndef AUTH_H
#define AUTH_H

#include "../types.h"

int register_user(User* users, int* uc, Account* accounts, int* ac);
int login_user(User* users, int uc, int* out_id);

#endif

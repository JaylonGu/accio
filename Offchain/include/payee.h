#ifndef PAYEE_H
#define PAYEE_H

#include "types.h"
#include "util.h"

extern mclBnFr bal_t;

void checkInitial(commit_t cm, mclBnFr *r, signature_t sigma);
int pay(const char* amt_str);
int checkPay(commit_t cm, signature_t sig);

#endif
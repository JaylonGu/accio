#ifndef PAYER_H
#define PAYER_H

#include "types.h"
#include "util.h"
#include <secp256k1.h>
#include <secp256k1_recovery.h>
#include "random.h"

int update(const char* amt_str, commit_t cm, signature_t sigma);
int checkUpdate(commit_t cm, signature_t sig);
#endif
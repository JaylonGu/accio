#ifndef TUMBLER_H
#define TUMBLER_H

#include <secp256k1_recovery.h>
#include "types.h"
#include "util.h"

void initialize(const char* id_str);
int updateConfirm(mclBnFr *bal, mclBnFr *amt, commit_t cm, secp256k1_ecdsa_recoverable_signature sig, signature_t sig_hat);

#endif
#ifndef UTIL_H
#define UTIL_H

#include <secp256k1.h>
#include <secp256k1_recovery.h>
#include "types.h"

#define CLOCK_PRECISION 1E9

extern const char G_STR[];
extern const char P_STR[];
extern const char G_HAT_STR[];
extern const char BAL[]; // 1 Ether
// extern const char PAYER_ID[];
// extern const char TUMBLER_ID[];
// extern const char PAYEE_ID[];

extern sk_t payeeSk, tumblerSk, payerSk;
extern vk_t payeeVk, tumblerVk, payerVk;
extern mclBnG2 G_hat;
extern mclBnG1 G,P;
// extern status_t st0, st1;

extern mclBnFr fund, amt;
extern mclBnFr bal_s, bal_s_tmp, bal_t;
extern mclBnFr r_1;

extern secp256k1_context* ctx;
extern secp256k1_ecdsa_recoverable_signature sig_0;
extern char sig_0_cpt[65];
extern unsigned char seckey_payer[32];
extern secp256k1_pubkey pubkey;

extern commit_t cm_0, cm_0_old, cm_1;
extern signature_t sig_hat_0, sig_hat_1; 

extern char id_0[20], id_1[20];

void init();
void hexReverse(char* src, size_t length);
int isSmaller(mclBnFr *a, mclBnFr *b);
long long ttimer(void);
void commit(const char* id_str, commit_t cm, mclBnFr *r);
// void cHomo(commit_t c, const char* amt_str);
void cHomo(commit_t c, mclBnFr *amt);
int cOpen(commit_t c, const char* id_str, mclBnFr *r);
void cSign(commit_t c, sk_t sk, signature_t sig);
int cVf(commit_t c, signature_t sigma, vk_t vk);
// void cRdm(commit_t c, signature_t sigma, mclBnFr *r);
void cRdm(commit_t c, signature_t sigma, commit_t c_ret, signature_t sigma_ret, mclBnFr *r);


#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <secp256k1.h>
#include <tomcrypt.h>
#include "types.h"
#include "util.h"
#include "tumbler.h"

// cm_1, r_1, sig_hat_1 发送给 Payee，让Payee初始化通道1状态
// 初始化tumbler余额 fund 和 payer的余额 bal_s

void initialize(const char* id_str){
    commit(id_str, cm_1, &r_1);
    cSign(cm_1, tumblerSk, sig_hat_1);

    mclBnFr_setStr(&fund, BAL, strlen(BAL), 10);
    bal_s = fund;
    // printf("Initialize message size: %.3f KB\n", (sizeof(commit_st)+sizeof(mclBnFr)+sizeof(signature_st))/1024.0);
}

// 收到的msg包含更新后的bal_s_tmp,amt,cm_1
// 检验对msg的签名是否合法
// 对cm_1进行同态运算，得到cm_0
// 对cm_0签名得到新sig_hat_0
// 把cm_0, sig_hat_0发送给Payer
int updateConfirm(mclBnFr *bal, mclBnFr *amt, commit_t cm, secp256k1_ecdsa_recoverable_signature sig, signature_t sig_hat){
    mclBnFr diff;
    mclBnFr_sub(&diff, &bal_s, amt);

    if(!mclBnFr_isEqual(&diff, bal) || mclBnFr_isNegative(bal) || mclBnFr_isNegative(amt) || !cVf(cm, sig_hat, tumblerVk) ) return -1;

    char buf[33]; 
    uint8_t *msg = malloc(32*7);
    size_t length;
    length = mclBnFr_serialize(buf, 33, bal);
    hexReverse(buf, 32);
    memcpy(msg, buf, 32);
    length = mclBnFr_serialize(buf, 33, amt);
    hexReverse(buf, 32);
    memcpy(msg+32, buf, 32);

    mclBnG1 c0n, c1n;
    mclBnG1_normalize(&c0n, &(cm->c0));
    mclBnG1_normalize(&c1n, &(cm->c1));
    length = mclBnFp_serialize(buf, 33, &(c0n.x));
    hexReverse(buf, 32);
    memcpy(msg+32*2, buf, 32);
    length = mclBnFp_serialize(buf, 33, &(c0n.y));
    hexReverse(buf, 32);
    memcpy(msg+32*3, buf, 32);
    length = mclBnFp_serialize(buf, 33, &(c1n.x));
    hexReverse(buf, 32);
    memcpy(msg+32*4, buf, 32);
    length = mclBnFp_serialize(buf, 33, &(c1n.y));
    hexReverse(buf, 32);
    memcpy(msg+32*5, buf, 32);
    memset(msg+32*6, 0, 12);
    memcpy(msg+32*6+12, id_0, 20);

    int idx = find_hash("keccak256");
    unsigned char msg_hash[MAXBLOCKSIZE];
    unsigned long len = sizeof(msg_hash);
    int err = hash_memory(idx, msg, 32*7, msg_hash, &len);
    
    // char prefix[29]= "\031Ethereum Signed Message:\n32";
    // char msgandprefix[60];
    // for(int i=0; i<32; i++){
    //     msgandprefix[28+i] = msg_hash[i];
    // }
    // for(int i=0; i<28; i++){
    //     msgandprefix[i] = prefix[i];
    // }
    // err = hash_memory(idx, msgandprefix, 60, msg_hash, &len);
    
    secp256k1_ecdsa_signature sig_norm;
    secp256k1_ecdsa_recoverable_signature_convert(ctx, &sig_norm, &sig);

    if(!secp256k1_ecdsa_verify(ctx, &sig_norm, msg_hash, &pubkey)) return -1;
    // printf("Update is confirmed\n");

    cm_0_old->c0 = cm->c0;
    cm_0_old->c1 = cm->c1;
    cm_0->c0 = cm->c0;
    cm_0->c1 = cm->c1;

    // type0 state is finalized here
    bal_s = diff;
    cHomo(cm_0, amt);
    cSign(cm_0, tumblerSk, sig_hat_0);

    // printf("UpdateConfirm message size: %.3f KB\n", (sizeof(commit_st) + sizeof(signature_st))/1024.0);
}
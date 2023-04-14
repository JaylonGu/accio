#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <secp256k1.h>
#include <secp256k1_recovery.h>
#include <tomcrypt.h>
#include "types.h"
#include "util.h"
#include "payer.h"
#include "random.h"


// 得到Payee要求收钱的消息，更新通道0的状态

int update(const char* amt_str, commit_t cm, signature_t sigma){
    if(amt_str[0]=='-') return -1;

    mclBnFr_setStr(&amt, amt_str, strlen(amt_str), 10);
    if(isSmaller(&bal_s, &amt) || !cVf(cm, sigma, tumblerVk)) return -1;

    mclBnFr_sub(&bal_s_tmp, &bal_s, &amt);

    // 对交易后余额bal_s_tmp, 交易金额amt, cm0 进行签名
    // 发送 上述消息，签名，sig_hat_0 给 tumbler
    char buf[32]; 
    uint8_t *msg = malloc(32*4);
    size_t length;
    length = mclBnFr_serialize(buf, 32, &bal_s_tmp);
    hexReverse(buf, 32);
    memcpy(msg, buf, 32);
    length = mclBnFr_serialize(buf, 32, &amt);
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

    int idx = find_hash("keccak256");
    unsigned char msg_hash[MAXBLOCKSIZE];
    unsigned long len = sizeof(msg_hash);
    int err = hash_memory(idx, msg, 32*6, msg_hash, &len);

    // printf("original hash:");
    // print_hex(msg_hash, 32);

    // char prefix[29]= "\031Ethereum Signed Message:\n32";
    // char msgandprefix[60];
    // for(int i=0; i<32; i++){
    //     msgandprefix[28+i] = msg_hash[i];
    // }
    // for(int i=0; i<28; i++){
    //     msgandprefix[i] = prefix[i];
    // }

    // err = hash_memory(idx, msgandprefix, 60, msg_hash, &len);

    // print_hex(msg, 32*6);
    // print_hex(msg_hash, 32);

    int return_val;
    secp256k1_ecdsa_sign_recoverable(ctx, &sig_0, msg_hash, seckey_payer, NULL, NULL);
    int recid;
    secp256k1_ecdsa_recoverable_signature_serialize_compact(ctx, sig_0_cpt, &recid, &sig_0);
    sig_0_cpt[64] = (char) recid+0x1b;

    // printf("Update message size: %.3f KB\n", (sizeof(msg) + sizeof(sig_0_cpt) + sizeof(signature_st))/1024.0);
}

// 检查新cm_0和新sig_hat_0
// 检查通过则发送给payee

int checkUpdate(commit_t cm, signature_t sig){
    commit_t cm_check;
    commit_new(cm_check);
    cm_check->c0 = cm_1->c0;
    cm_check->c1 = cm_1->c1;

    cHomo(cm_check, &amt);

    if(!mclBnG1_isEqual(&(cm->c0),&(cm_check->c0)) || !mclBnG1_isEqual(&(cm->c1),&(cm_check->c1)) || !cVf(cm, sig, tumblerVk)) return -1;
    // if( !mclBnG1_isEqual(&(cm->c0),&(cm_check->c0)) ) return -1;

    // printf("Update is checked\n");
    // printf("CheckUpdate message size: %.3f KB\n", (sizeof(commit_st) + sizeof(signature_st))/1024.0);
    commit_free(cm_check);
}
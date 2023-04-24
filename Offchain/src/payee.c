#include <stdio.h>
#include <mcl/bn_c256.h>
#include <string.h>
#include "types.h"
#include <stdio.h>
#include "util.h"
#include "payee.h"

// 检验tumbler发来的Initialize的消息
// 设置tumbler的余额 bal_t
// 把签名和承诺随机化，得到新的 cm，sig_hat_1和r'，以r+r'作为状态r
void checkInitial(commit_t cm, mclBnFr *r, signature_t sigma){
    if(!cOpen(cm, id_1, r) || !cVf(cm, sigma, tumblerVk)) return;  
    // printf("CheckInitial is successful.\n");
    mclBnFr r_;

    cRdm(cm, sigma, cm_1, sig_hat_1, &r_);
    mclBnFr_add(&r_1, r, &r_);

    mclBnFr_setStr(&bal_t, BAL, strlen(BAL), 10);
}

// 给payer 发送收钱的消息
int pay(const char* amt_str){
    if(amt_str[0]=='-') return -1;
    mclBnFr amt;
    mclBnFr_setStr(&amt, amt_str, strlen(amt_str),10);
    if(isSmaller(&bal_t,&amt)) return -1;

    // printf("Pay message size: %.3f KB\n", (sizeof(commit_st)+sizeof(signature_st))/1024.0);
}

// payee检查cm_0和sig_hat_0
// 检查通过则把签名和承诺随机化，得到新的 cm，sig_hat_1和r'，以r+r'作为状态r
int checkPay(commit_t cm, signature_t sig){
    commit_t cm_check;
    commit_new(cm_check);
    cm_check->c0 = cm_1->c0;
    cm_check->c1 = cm_1->c1;
    cHomo(cm_check, &amt);

    if(!mclBnG1_isEqual(&(cm->c0),&(cm_check->c0)) || !mclBnG1_isEqual(&(cm->c1),&(cm_check->c1)) || !cVf(cm, sig, tumblerVk)) return -1;

    // printf("Pay is checked\n");
    
    mclBnFr r_;
    cRdm(cm, sig, cm_1, sig_hat_1, &r_);

    mclBnFr_sub(&bal_t, &bal_t, &amt);

    mclBnFr_add(&r_1, &r_1, &r_);
    // type 1 state is finalized here
    commit_free(cm_check);
}
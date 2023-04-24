#include <string.h>
#include <mcl/bn_c256.h>
#include <tomcrypt.h>
#include <time.h>
#include "util.h"
#include "types.h"
#include "payer.h"

const char G_STR[] = "1 1 2";
const char P_STR[] = "1 1368015179489954701390400359078579693043519447331113978918064868415326638035 9918110051302171585080402603319702774565515993150576347155970296011118125764";
const char G_HAT_STR[] = "1 10857046999023057135944570762232829481370756359578518086990519993285655852781 11559732032986387107991004021392285783925812861821192530917403151452391805634 8495653923123431417604973247489272438418190587263600148770280649306958101930 4082367875863433681332203403145435568316851327593401208105741076214120093531";
const char BAL[] = "1000000000000000000"; // 1 Ether

sk_t payeeSk, tumblerSk, payerSk;
vk_t payeeVk, tumblerVk, payerVk;
mclBnG2 G_hat;
mclBnG1 G,P;

mclBnFr fund, amt;
mclBnFr bal_s, bal_s_tmp, bal_t;
mclBnFr r_1;

secp256k1_context* ctx;
secp256k1_ecdsa_recoverable_signature sig_0;
char sig_0_cpt[65];
unsigned char seckey_payer[32] = {0};
secp256k1_pubkey pubkey;

commit_t cm_0, cm_0_old, cm_1;
signature_t sig_hat_0, sig_hat_1; 

void init(){
    mclBn_init(MCL_BN_SNARK1, MCLBN_COMPILED_TIME_VAR);

    mclBnG1_setStr(&G, G_STR, strlen(G_STR), 10);
    mclBnG1_setStr(&P, P_STR, strlen(P_STR), 10);
    mclBnG2_setStr(&G_hat, G_HAT_STR, strlen(G_HAT_STR), 10);

    sk_new(payeeSk);
    sk_new(tumblerSk);
    sk_new(payerSk);

    vk_new(payeeVk);
    vk_new(tumblerVk);
    vk_new(payerVk);

    mclBnFr_setInt(&payeeSk->x0,1);
    mclBnFr_setInt(&payeeSk->x1,1);
    mclBnFr_setInt(&tumblerSk->x0,1);
    mclBnFr_setInt(&tumblerSk->x1,1);
    mclBnFr_setInt(&payerSk->x0,1);
    mclBnFr_setInt(&payerSk->x1,1);

    payeeVk->x0=G_hat;
    payeeVk->x1=G_hat;
    tumblerVk->x0=G_hat;
    tumblerVk->x1=G_hat;
    payerVk->x0=G_hat;
    payerVk->x1=G_hat;

    commit_new(cm_1);
    commit_new(cm_0);
    commit_new(cm_0_old);
    signature_new(sig_hat_1);
    signature_new(sig_hat_0);

    // 可以在这里改payer的私钥
    char* key = "83178e274bbb3c31819c399027df63ac80a2b654012325da3712110c9cd031f4";
    for (int i = 0; i < 64; i += 2)
    {
        char slice[3]={0};
        slice[0] = key[i] ;
        slice[1] = key[i+1];
        sscanf(slice, "%hhx", seckey_payer + i / 2);
    }

    ctx = secp256k1_context_create(SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
    int return_val = secp256k1_ec_pubkey_create(ctx, &pubkey, seckey_payer);
    register_hash(&keccak_256_desc);
}

void hexReverse(char* src, size_t length){
    if(length == 32){
        char tmp;
        for(int i=0; i<16; ++i){
            tmp = src[i];
            src[i] = src[31-i];
            src[31-i] = tmp;
        }
    }else{
        char tmp;
        for(int i=0; i<16; ++i){
            tmp = src[i];
            src[i] = src[31-i];
            src[31-i] = tmp;
        }
        for(int i=0; i<16; ++i){
            tmp = src[32+i];
            src[32+i] = src[63-i];
            src[63-i] = tmp;
        }        
    }
}

// get first 128bits and change first 3 bits as 000
void bytesToHexString(unsigned char* hex, unsigned char* str, int hexlen){
    unsigned char left = (hex[0] >> 4) & 1;
    unsigned char right = hex[0] & 0xf;
    if(left) {
        str[0]='1';
    }else{
        str[0]='0';
    }
    if(right>=0x00 && right <= 0x09){
            str[1] = right + 0x30;
    }else{
        str[1] = right + 'a' - 0xa;
    }
    for(int i = 1;i < hexlen; ++i){
        int j = 2 * i;
        left = hex[i] >> 4;
        right = hex[i] & 0xf;
        if(left>=0x00 && left <= 0x09){
            str[j] = left + 0x30;
        }else{
            str[j] = left + 'a' - 0xa;
        }
        if(right>=0x00 && right <= 0x09){
            str[j+1] = right + 0x30;
        }else{
            str[j+1] = right + 'a' - 0xa;
        }
    }
}


int isSmaller(mclBnFr *a, mclBnFr *b){
    mclBnFr diff;
    mclBnFr_sub(&diff, a, b);
    return mclBnFr_isNegative(&diff);
}

long long ttimer(void) {
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return (long long) (time.tv_sec * CLOCK_PRECISION + time.tv_nsec);
}

// void printChar(const char* str){
//     for(int i=0; i<64; i++){
//         printf("%c",str[i]);
//     }
//     printf("\n");
// }

void parseMessage(const char* msg, mclBnG1 *m){
    register_hash(&keccak_256_desc);
    int idx = find_hash("keccak256");
    unsigned char msg_hash[MAXBLOCKSIZE]={0};
    unsigned long len = sizeof(msg_hash);
    hash_memory(idx, msg, 20, msg_hash, &len);
    // print_hex(msg_hash,32);
    unsigned char mc[64];
    bytesToHexString(msg_hash, mc, 32);
    for(int i = 32; i<64 ; ++i){
        mc[i] = '0';
    }
    mclBnFr k;
    mclBnFr_setStr(&k, mc, 64, 16);

    mclBnG1_mul(m, &G, &k);
}

void commit(const char* id_str, commit_t cm, mclBnFr *r){
    mclBnG1 m, rp;
    parseMessage(id_str, &m);
    mclBnFr_setInt(r,1);
    mclBnG1_mul(&(cm->c0), &G, r);

    mclBnG1_mul(&rp, &P, r);
    mclBnG1_add(&(cm->c1), &m, &rp);
}

// Directly make changes on c
// void cHomo(commit_t c, const char* amt_str){
//     mclBnFr amt;
//     mclBnFr_setStr(&amt, amt_str, strlen(amt_str), 10);

//     mclBnG1 a;
//     mclBnG1_mul(&a, &G, &amt);

//     mclBnG1_add(&(c->c1), &(c->c1), &a);
// }

void cHomo(commit_t c, mclBnFr *amt){
    mclBnG1 a;
    mclBnG1_mul(&a, &G, amt);

    mclBnG1_add(&(c->c1), &(c->c1), &a);
}

int cOpen(commit_t c, const char* id_str, mclBnFr *r){
    mclBnG1 m, r1, r2;
    int b1,b2;
    parseMessage(id_str, &m);
    
    mclBnG1_mul(&r1, &G, r);
    b1 = mclBnG1_isEqual(&(c->c0), &r1);

    mclBnG1_mul(&r1, &P, r);
    mclBnG1_add(&r2, &m, &r1);
    b2 = mclBnG1_isEqual(&(c->c1), &r2);

    // printf("isValid: %d, isZero: %d\n", mclBnG1_isValid(&m), mclBnG1_isZero(&m));
    
    return b1 && b2;
}

void cSign(commit_t c, sk_t sk, signature_t sig){
    mclBnG1 z,z1,z2,z3,t;
    mclBnFr s_int,s_inv;

    mclBnFr_setInt(&s_int, 1);
    mclBnFr_inv(&s_inv, &s_int);   

    mclBnG1_mul(&z1, &(c->c0), &(sk->x0));
    mclBnG1_mul(&z2, &(c->c1), &(sk->x1));
    mclBnG1_add(&z3, &z1, &G);
    mclBnG1_add(&z, &z3, &z2);
    mclBnG1_mul(&(sig->z), &z, &s_inv);
    
    mclBnG1_mul(&(sig->s), &G, &s_int);

    mclBnG2_mul(&(sig->s_hat), &G_hat, &s_int);

    mclBnG1_mul(&z1, &G, &(sk->x0));
    mclBnG1_mul(&z2, &P, &(sk->x1));
    mclBnG1_add(&z3, &z1, &z2);
    mclBnG1_mul(&(sig->t), &z3, &s_inv);
}

int cVf(commit_t c, signature_t sigma, vk_t vk){
    if(mclBnG1_isZero(&(sigma->s))){
        return 0;
    }
    mclBnGT zs_hat, gg_hat, c0x0, c1x1, gs_hat, sg_hat, ts_hat, gx0, px1;
    mclBnGT r1,r2;
    int b1,b2,b3;  

    mclBn_pairing(&zs_hat, &(sigma->z), &(sigma->s_hat));
    mclBn_pairing(&gg_hat, &G, &G_hat);
    mclBn_pairing(&c0x0, &(c->c0), &(vk->x0));
    mclBn_pairing(&c1x1, &(c->c1), &(vk->x1));
    mclBnGT_mul(&r1,&gg_hat,&c0x0);
    mclBnGT_mul(&r2,&r1,&c1x1);
    b1 = mclBnGT_isEqual(&zs_hat,&r2);

    mclBn_pairing(&gs_hat, &G, &(sigma->s_hat));
    mclBn_pairing(&sg_hat, &(sigma->s), &G_hat);
    b2 = mclBnGT_isEqual(&gs_hat, &sg_hat);

    mclBn_pairing(&ts_hat, &(sigma->t), &(sigma->s_hat));
    mclBn_pairing(&gx0, &G, &(vk->x0));
    mclBn_pairing(&px1, &P, &(vk->x1));
    mclBnGT_mul(&r1, &gx0, &px1);
    b3 = mclBnGT_isEqual(&ts_hat, &r1);

    return b1 && b2 && b3;
}

// void cRdm(commit_t c, signature_t sigma, mclBnFr *r){
//     mclBnFr s, s_inv;
//     mclBnFr_setByCSPRNG(r);
//     mclBnFr_setByCSPRNG(&s);
//     mclBnFr_inv(&s_inv, &s);

//     mclBnG1 tmp;
//     mclBnG1_mul(&tmp, &G, r);
//     mclBnG1_add(&(c->c0), &(c->c0), &tmp);
//     mclBnG1_mul(&tmp, &P, r);
//     mclBnG1_add(&(c->c1), &(c->c1), &tmp);

//     mclBnG1_mul(&tmp,&(sigma->t), r);
//     mclBnG1_add(&tmp, &tmp, &(sigma->z));
//     mclBnG1_mul(&(sigma->z), &tmp, &s_inv);

//     mclBnG1_mul(&(sigma->s), &(sigma->s), &s);

//     mclBnG2_mul(&(sigma->s_hat), &(sigma->s_hat), &s);

//     mclBnG1_mul(&(sigma->t), &(sigma->t), &s_inv);
// }

void cRdm(commit_t c, signature_t sigma, commit_t c_ret, signature_t sigma_ret, mclBnFr *r){
    mclBnFr s, s_inv;
    mclBnFr_setByCSPRNG(r);
    mclBnFr_setByCSPRNG(&s);
    mclBnFr_inv(&s_inv, &s);

    mclBnG1 tmp;
    mclBnG1_mul(&tmp, &G, r);
    mclBnG1_add(&(c_ret->c0), &(c->c0), &tmp);
    mclBnG1_mul(&tmp, &P, r);
    mclBnG1_add(&(c_ret->c1), &(c->c1), &tmp);

    mclBnG1_mul(&tmp,&(sigma->t), r);
    mclBnG1_add(&tmp, &tmp, &(sigma->z));
    mclBnG1_mul(&(sigma_ret->z), &tmp, &s_inv);

    mclBnG1_mul(&(sigma_ret->s), &(sigma->s), &s);

    mclBnG2_mul(&(sigma_ret->s_hat), &(sigma->s_hat), &s);

    mclBnG1_mul(&(sigma_ret->t), &(sigma->t), &s_inv);
}
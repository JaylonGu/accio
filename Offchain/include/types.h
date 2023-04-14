#ifndef TYPES_H
#define TYPES_H

#include <mcl/bn_c256.h>
#include <secp256k1.h>
#include <stdlib.h>

typedef struct{
    mclBnFr x0,x1;
}sk_st;

typedef sk_st *sk_t;

#define sk_new(params)                       \
    do {                                     \
        params = malloc(sizeof(sk_st));      \
    } while(0)                               \

#define sk_free(params)                     \
    do{                                     \
        free(params);                        \
        params = NULL;                       \
    }while(0)

typedef struct{
    mclBnG2 x0,x1;
}vk_st;

typedef vk_st *vk_t;

#define vk_new(params)                       \
    do {                                     \
        params = malloc(sizeof(vk_st));      \
    } while(0)                               \

#define vk_free(params)                     \
    do{                                     \
        free(params);                        \
        params = NULL;                       \
    }while(0)

typedef struct{
    mclBnG1 c0,c1;
}commit_st;

typedef commit_st *commit_t;

#define commit_new(params)                       \
    do {                                     \
        params = malloc(sizeof(commit_st));      \
    } while(0)                               \

#define commit_free(params)                     \
    do{                                     \
        free(params);                        \
        params = NULL;                       \
    }while(0)

typedef struct{
    mclBnG1 z,s,t;
    mclBnG2 s_hat;
}signature_st;

typedef signature_st *signature_t;

#define signature_new(params)                       \
    do {                                     \
        params = malloc(sizeof(signature_st));      \
    } while(0)                               \

#define signature_free(params)                     \
    do{                                     \
        free(params);                        \
        params = NULL;                       \
    }while(0)

// typedef struct{
//     mclBnFr bal;
//     commit_t cm;
//     signature_t sig_hat;
//     mclBnFr amt;
//     secp256k1_ecdsa_signature sig;
// }status_st;

// typedef status_st *status_t;
#endif
#ifndef WATERS_IBE_H
#define WATERS_IBE_H
#include <pbc.h>
#include <pbc_test.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 

#define WATERS_ID_BITS 32

struct public_parameters{
	element_t g;
	//element_t g1;
	element_t g2;
	element_t uu;
	element_t* U;
	pairing_t pairing;
};
typedef struct public_parameters* public_parameters;

typedef element_t dk[2];
typedef element_t ct[3];

void zk_proof(element_t s,element_t P,element_t P1,element_t T,element_t c, element_t w, pairing_t pairing);

int waters_pkVerify(element_t w,element_t T,element_t c,element_t P, element_t P1,pairing_t pairing);

void waters_commonsetup(public_parameters pp);

void waters_keysetup(public_parameters pp, element_t sk, element_t g1);

void waters_keyder(dk dk1, public_parameters pp,element_t sk, int id);

void waters_pCombine(element_t g1r,element_t g1a,element_t g1b); //pCombine

void waters_kCombine(dk dkf,dk dk1,dk dk2);//kCombine

void waters_enc(ct CT, public_parameters pp,element_t g1, int id, element_t M);//unsigned char* M);

void waters_dec(element_t M, public_parameters pp, ct C, dk dk1);

int waters_enc_dec( public_parameters pp, element_t g1,int id, dk dk1);

int waters_dkVerify(public_parameters pp,element_t g1, int id,dk dk1);

void waters_clear_pp(public_parameters pp);


#endif

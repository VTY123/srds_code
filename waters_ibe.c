//#include <pbc.h>
//#include <pbc_test.h>
//#include <pthread.h>
#include "./waters_ibe.h"
/*
To do 

check the consistency to Waters paper 

*/


void zk_proof(element_t s,element_t P,element_t P1,element_t T,element_t c, element_t w, pairing_t pairing){
	//use function parameters to return the zero knowledge proof


	element_t u;
	element_init_G1(u,pairing);
	element_random(u);
	
	element_t r;
	element_init_Zr(r,pairing);
	element_random(r);

	element_init_G1(T,pairing);
	element_mul_zn(T,P,r);

	unsigned char* data = malloc(4*element_length_in_bytes(u));

	//convert group elements to data for hash
	element_to_bytes(data,u);
	element_to_bytes(data+element_length_in_bytes(u),P);	

	element_to_bytes(data + 
		element_length_in_bytes(u) + element_length_in_bytes(P),P1);

	element_to_bytes(data + 
		element_length_in_bytes(u) + element_length_in_bytes(P)
		+ element_length_in_bytes(P1),T);

	int hash_len = element_length_in_bytes(u) + element_length_in_bytes(P)
			+ element_length_in_bytes(P1) 
				+ element_length_in_bytes(T);
	
	//hash all data
	element_init_Zr(c,pairing);
	element_from_hash(c,data,hash_len);

	element_init_Zr(w,pairing);
	element_mul(w,c,s);
	element_add(w,w,r);

}


int waters_pkVerify(element_t w,element_t T,element_t c,element_t P, element_t P1,pairing_t pairing){
//pkVerify: verify the zero knowledge proof
	element_t wP;
	element_init_G1(wP,pairing);
	element_mul_zn(wP,P,w);

	element_t cP;
	element_init_G1(cP,pairing);

	element_mul_zn(cP,P1,c);
	
	element_t tP;
	element_init_G1(tP,pairing);
	element_add(tP,T,cP);

	int t = element_cmp(wP,tP);
	return t;
}


void waters_commonsetup(public_parameters pp){
	//initialize the common public parameters for Waters IBE
	element_init_G1(pp->g,pp->pairing);
	element_random(pp->g);	

	element_init_G2(pp->g2,pp->pairing);
	element_random(pp->g2);

	element_init_G2(pp->uu,pp->pairing);
	element_random(pp->uu);
	pp->U = malloc(sizeof(element_t)*WATERS_ID_BITS);
	for (int i = 0; i < WATERS_ID_BITS;i++){
		element_init_G2(pp->U[i],pp->pairing);
		element_random(pp->U[i]);
	}	
}

void waters_keysetup(public_parameters pp, element_t sk,element_t g1){
	//randomly sample the secret key 
	//and output it and its related public parameter 
	element_init_Zr(sk,pp->pairing);
	element_random(sk);
	element_init_G1(g1,pp->pairing);
	element_mul_zn(g1,pp->g,sk);
}

void waters_keyder(dk dk1, public_parameters pp,element_t msk, int id){
	//KeyDer algorithm of Waters IBE
	element_t r;
	element_init_Zr(r,pp->pairing);
	element_random(r);

	element_init_G2(dk1[0],pp->pairing);
	element_set(dk1[0],pp->uu);
	for (int i = 0; i < WATERS_ID_BITS;i++){
		if ((1 << i) & id){
			element_add(dk1[0],dk1[0],pp->U[i]);	
		}
	}
	element_mul_zn(dk1[0],dk1[0],r);

	element_t g2a;
	element_init_G2(g2a,pp->pairing);
	element_mul_zn(g2a,pp->g2,msk);
	element_add(dk1[0],dk1[0],g2a);

	element_init_G1(dk1[1],pp->pairing);
	element_mul_zn(dk1[1],pp->g,r);

	element_clear(r);
	element_clear(g2a);
}

void waters_pCombine(element_t g1r,element_t g1a,element_t g1b){
	//combine contributions of public parameters
	element_add(g1r,g1a,g1b);
}

void waters_kCombine(dk dkf,dk dk1,dk dk2){
	
	element_add(dkf[0],dk1[0],dk2[0]);
	element_add(dkf[1],dk1[1],dk2[1]);
}

void waters_enc(ct CT, public_parameters pp, element_t g1,int id, element_t M ){
	element_t t;
	element_init_Zr(t,pp->pairing);
	element_random(t);
	element_init_GT(CT[0],pp->pairing);
	element_pairing(CT[0],g1,pp->g2);
	element_mul_zn(CT[0],CT[0],t);
	element_add(CT[0],CT[0],M);

	element_init_G1(CT[1],pp->pairing);
	element_mul_zn(CT[1],pp->g,t);

	element_init_G2(CT[2],pp->pairing);//2
	element_set(CT[2],pp->uu);
	for(int i = 0; i < WATERS_ID_BITS;i++){
		if ((1 << i) & id){
			element_add(CT[2],CT[2],pp->U[i]);
		}
	}
	element_mul_zn(CT[2],CT[2],t);	
}

void waters_dec(element_t M, public_parameters pp, ct CT, dk dk1){
	element_t t0,t1;
	element_init_GT(t0,pp->pairing);
	element_init_GT(t1,pp->pairing);
	element_pairing(t0,dk1[1],CT[2]);

	element_neg(CT[1],CT[1]);
	element_pairing(t1,CT[1],dk1[0]);
	element_add(t0,t1,t0);

	element_add(CT[0],CT[0],t0);	

	element_init_GT(M,pp->pairing);
	element_set(M,CT[0]);

	element_clear(t0);
	element_clear(t1);
}

int waters_enc_dec(public_parameters pp, element_t g1, int id, dk dk1){
	element_t M;
	element_init_GT(M,pp->pairing);
	element_random(M);
	ct CT;
    waters_enc(CT, pp, g1, id, M);

	element_t CM;
    waters_dec(CM, pp, CT, dk1);

	for (int i =0; i < 3;i++){
		element_clear(CT[i]);
	}

	int ret = -1; 
	if( element_cmp(CM,M) == 0){
		ret = 0;
	}
	return ret;
}

int waters_dkVerify(public_parameters pp,element_t g1 ,int id,dk dk1){
	//verifying algorithm for decryption keys 

	element_t t1;
	element_init_G2(t1,pp->pairing);
	element_set(t1,pp->uu);
	for (int i = 0; i < WATERS_ID_BITS;i++){
		if ((1<<i) & id){
				element_add(t1,t1,pp->U[i]);
		}
	}
	element_neg(t1,t1);
	
	element_t tt;
	element_init_GT(tt,pp->pairing);
	element_pairing(tt,dk1[1],t1);

	element_t t0;
	element_init_GT(t0,pp->pairing);
	element_pairing(t0,pp->g,dk1[0]);
	element_add(tt,tt,t0);

	element_t p;
	element_init_GT(p,pp->pairing);
	element_pairing(p,g1,pp->g2);

	element_clear(t1);
	
	if(element_cmp(p,tt) == 0){
		element_clear(tt);
		return 0;
	}
	element_clear(p);
	element_clear(tt);
	return -1;

}

void waters_clear_pp(public_parameters pp){
	// clean up variables of public parameters
	element_clear(pp->g);
	element_clear(pp->g2);
	element_clear(pp->uu);
	for (int i = 0; i < WATERS_ID_BITS;i++){
		element_clear(pp->U[i]);
	}
	free(pp->U);
}



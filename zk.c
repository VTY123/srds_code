#include <pbc.h>
#include <pbc_test.h>

#include <stdlib.h>

typedef struct zk_proof{
	element_t T;
	element_t c;
	element_t w;
} zkp;


void* zk_proof(element_t s,element_t P,element_t P1,element_t T,element_t c, element_t w, pairing_t pairing){
	//element_t s;
	//element_init_Zr(s,pairing);
	//element_random(s);

	element_t u;
	element_init_G1(u,pairing);
	element_random(u);
	
	element_t r;
	element_init_Zr(r,pairing);
	element_random(r);

	//element_t T;
	element_init_G1(T,pairing);
	element_mul_zn(T,P,r);

	unsigned char* data = malloc(4*element_length_in_bytes(u));

	element_to_bytes(data,u);
	element_to_bytes(data+element_length_in_bytes(u),P);	

	element_to_bytes(data + 
		element_length_in_bytes(u) + element_length_in_bytes(P),P1);

	element_to_bytes(data + 
		element_length_in_bytes(u) + element_length_in_bytes(P)
		+ element_length_in_bytes(P1),T);
		
	//printf("s len = %d   P len = %d \n",element_length_in_bytes(s),
			//	element_length_in_bytes(P));

	int hash_len = element_length_in_bytes(u) + element_length_in_bytes(P)
			+ element_length_in_bytes(P1) 
				+ element_length_in_bytes(T);
	
	//element_t c;
	element_init_Zr(c,pairing);
	element_from_hash(c,data,hash_len);

	//element_t w;
	element_init_Zr(w,pairing);
	element_mul(w,c,s);
	element_add(w,w,r);
/*
	element_t wP;
	element_init_G1(wP,pairing);
	element_mul_zn(wP,P,w);

	element_t cP;
	element_init_G1(cP,pairing);

	element_mul_zn(cP,P1,c);
	
	element_t tP;
	element_init_G1(tP,pairing);
	element_add(tP,T,cP);

	int t = element_cmp(wP,tP);*/
	//printf(" t = %d\n",t);

	//zkp* zkptr = malloc(sizeof(zkp));

	return NULL;
}

int zk_verify(element_t T,element_t c,element_t w,element_t P, element_t P1,pairing_t pairing){

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
int main(int argc, char** argv){

	pairing_t pairing;
	pbc_demo_pairing_init(pairing,argc,argv);

	element_t s;
	element_init_Zr(s,pairing);
	element_random(s);


	element_t P;
	element_init_G1(P,pairing);
	element_random(P);

	element_t P1;
	element_init_G1(P1,pairing);
	element_mul_zn(P1,P,s);

	element_t T,c,w;


	double time1 = pbc_get_time();
for (int i = 0 ; i < 100;i++){
	zk_proof(s, P,P1,T,c,w ,pairing);

	
	int t = zk_verify(w,T,c,P,P1,pairing);
}
		element_printf(" w =  %B \n",w);

		double time2 = pbc_get_time();

	printf(" t = %f \n",time2 -time1);

/*	element_printf("E = %e \n",c);	

	printf("%s \n",data);

	for (int i = 0; i < element_length_in_bytes(u);i++){
		printf("%c",data[i]);
	}

	printf("%d\n",element_length_in_bytes(u));*/
	//element_from_hash();

}

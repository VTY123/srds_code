#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"

/*
	Highlight the trusted repository server computation
*/

// this benchmark focuses on the computation cost (ignore the communication cost)

//benchmark data is stored in the directory ./mst_ibe_data

// We separate the computation of key derivation
// and the computation of the kCombine for benchmark and observation.

// simulation assumes following running sequence:
// server runs CommonSetup -> all clients run KeySetup -> server runs pkVerify
// all clients run KeyDer -> server runs dkVerify ->server runs pCombine ->  server runs kCombine

// run enc and dec algorithms to verifying the decryption correctness

//pulse simulating add one more client

// Note: the communciation cost can be analyzed theoretically.

void sim_mst_ibe(pp pp, int num_client)
{
	char buf[128];
	// initialize clients' variables for secret keys and contributions of public parameters.
	element_t *clients_sk = malloc(sizeof(element_t) * (num_client + 1));
	element_t *clients_g1 = malloc(sizeof(element_t) * (num_client + 1));

	// initialize clients' variables for zero knowledge proof or pkVerify
	element_t *Tptr = malloc(num_client * sizeof(element_t));
	element_t *cptr = malloc(num_client * sizeof(element_t));
	element_t *wptr = malloc(num_client * sizeof(element_t));

	// benchmark the total time of keysetup algorithm
	double time1, time2;
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		waters_keysetup(pp, clients_sk[i], clients_g1[i]);
		zk_proof(clients_sk[i], pp->g, clients_g1[i], Tptr[i], cptr[i], wptr[i], pp->pairing);
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/keysetup.txt", buf);


	/*Reppository server computation BEGIN*/
	//benchmark pkVerify
	time1 = pbc_get_time();

	for (int i = 0; i < num_client; i++)
	{
		int t = waters_pkVerify(wptr[i], Tptr[i], cptr[i], pp->g, clients_g1[i], pp->pairing);
		if (t != 0)
		{
			printf("pkVerify fails\n");
		}
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/pkVerify.txt", buf);
	/*Reppository server computation END*/

	// Note: the verification time is the sum of the server computation and clients' computation

	dk **clients_dks = malloc(sizeof(dk *) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		clients_dks[i] = malloc(sizeof(dk) * num_client);
	}
	// benchmark keyder
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		for (int id = 1; id <= num_client; id++)
		{
			waters_keyder(clients_dks[i][id - 1], pp, clients_sk[i], id);
		}
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/keyder.txt", buf);


	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		for (int id = 1; id <= num_client; id++)
		{
			int r = waters_dkVerify(pp, clients_g1[i], id, clients_dks[i][id - 1]);
			if (r != 0)
			{
				printf("dkVerify fails\n");
			}
		}
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/dkVerify.txt", buf);

	// the trusted repository server computation BEGIN
	//benchmark pCombine
	element_t g1;
	element_init_G1(g1, pp->pairing);
	time1 = pbc_get_time();
	element_set(g1, clients_g1[0]);
	for (int i = 1; i < num_client; i++)
	{
		waters_pCombine(g1, g1, clients_g1[i]);
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/pCombine.txt", buf);
	// the trusted repository server computation END

	// benchmark kCombine
	dk *decryption_keys = malloc(sizeof(dk) * (num_client));
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		element_init_G1(decryption_keys[i][0], pp->pairing);
		element_init_G1(decryption_keys[i][1], pp->pairing);
		element_set(decryption_keys[i][0], clients_dks[0][i][0]);
		element_set(decryption_keys[i][1], clients_dks[0][i][1]);
		for (int j = 1; j < num_client; j++)
		{
			waters_kCombine(decryption_keys[i], decryption_keys[i], clients_dks[j][i]);
		}
	}

	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/kCombine.txt", buf);

	// FOR DEBUG: check final decrypotion keys
	
	for (int i = 0; i < num_client; i++)
	{
		int r = waters_dkVerify(pp, g1, i + 1, decryption_keys[i]);
		if (r != 0)
		{
			printf("final dkVerify fails\n");
		}
	}

	// FOR DEBUG: test and benchmarks for decrypotion and correctness
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		int r = waters_enc_dec(pp, g1, i + 1, decryption_keys[i]);
		if (r != 0)
		{
			printf("enc dec fail\n");
		}
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/enc_dec.txt", buf);

	/*add one client*/
	element_t ns;
	element_t npp;
	dk *nc = malloc(sizeof(dk) * num_client);

//benchamark adding one more client
	time1 = pbc_get_time();
	waters_keysetup(pp, ns, npp);
	// verification

	element_t nT;
	element_t ncc;
	element_t nw;

	zk_proof(ns, pp->g, npp, nT, ncc, nw, pp->pairing);

	/*the trusted repository server computation BEGIN*/

	int t = waters_pkVerify(nw, nT, ncc, pp->g, npp, pp->pairing);
	if (t != 0)
	{
		element_printf("pkVerify fails\n");
	}


	for (int i = 0; i < num_client; i++)
	{
		waters_keyder(nc[i], pp, ns, i + 1);
	}

	/*the trusted repository server computation BEGIN */
	waters_pCombine(g1, g1, npp);
	/*the trusted repository server computation END */

	int c_id = 123456;
	dk *cd = malloc(sizeof(dk) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		waters_kCombine(decryption_keys[i], decryption_keys[i], nc[i]);
		waters_keyder(cd[i], pp, clients_sk[i], c_id);
	}

	dk ncd;
	waters_keyder(ncd, pp, ns, c_id);
	for (int i = 0; i < num_client; i++)
	{
		waters_kCombine(ncd, ncd, cd[i]);
	}


	// uncomment when benchmark adding verification
	
//one more test or many tests?


	for (int i = 0; i < num_client; i++)
	{
		if (waters_dkVerify(pp, npp,i+1,nc[i]) != 0)
		{
			printf(" i = %d fail \n", i);
		}
		if (waters_dkVerify(pp,clients_g1[i],c_id,cd[i]) != 0)
		{
			printf(" i = %d fail \n", i);
		}
	}
	
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	append_to_file("mst_ibe_data/addClient.txt", buf);
	
	//FOR DEBUG
	if (waters_dkVerify(pp, g1, c_id, ncd) != 0)
	{
		printf("dkVerify fail\n");
	}
	
	element_clear(ns);
	element_clear(npp);
	for (int i = 0; i < num_client; i++)
	{
		element_clear(nc[i][0]);
		element_clear(nc[i][1]);
		element_clear(clients_sk[i]);
		element_clear(clients_g1[i]);
		element_clear(decryption_keys[i][0]);
		element_clear(decryption_keys[i][1]);
		element_clear(cd[i][0]);
		element_clear(cd[i][1]);
	}
	free(nc);
	free(clients_sk);
	free(clients_g1);
	free(decryption_keys);
	free(cd);

	element_clear(ncd[0]);
	element_clear(ncd[1]);
	element_clear(g1);

	for (int i = 0; i < num_client; i++)
	{
		for (int j = 0; j < num_client; j++)
		{
			element_clear(clients_dks[i][j][0]);
			element_clear(clients_dks[i][j][1]);
		}
		free(clients_dks[i]);
	}
	free(clients_dks);
}

int main(int argc, char **argv)
{
	pp pp = malloc(sizeof(struct public_parameters));
	pbc_demo_pairing_init(pp->pairing, argc, argv);
	waters_commonsetup(pp);

	int arr[11] = {0};
	/*
	arr[0] = 200;
	arr[1] = 600;
	arr[2] = 1000;
*/
	arr[0] = 1;
	for (int i = 1; i <= 10;i++){
		arr[i] = i*100;
	}

//for (int k = 0; i < 3;k++)
	for (int k = 0; k < 11; k++)
	{
		sim_mst_ibe(pp, arr[k]);
	}
	free(pp);
}

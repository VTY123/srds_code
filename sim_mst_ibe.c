#include "./sim_mst_ibe.h"

void sim_mst_ibe(public_parameters pp, int num_client, int verification_flag, char *dir)
{
	char pth[128];
	strcpy(pth, dir);

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
	strcpy(pth + strlen(dir), "/keysetup.txt");
	append_to_file(pth, buf);

	/*Reppository server computation BEGIN*/
	// benchmark pkVerify
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
	strcpy(pth + strlen(dir), "/pkVerify.txt");
	append_to_file(pth, buf);
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
	strcpy(pth + strlen(dir), "/keyder.txt");
	append_to_file(pth, buf);

	// benchmark dkVerify
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
	strcpy(pth + strlen(dir), "/dkVerify.txt");
	append_to_file(pth, buf);

	// the trusted repository server computation BEGIN
	// benchmark pCombine
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
	strcpy(pth + strlen(dir), "/pCombine.txt");
	append_to_file(pth, buf);

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
	strcpy(pth + strlen(dir), "/kCombine.txt");
	append_to_file(pth, buf);

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
	strcpy(pth + strlen(dir), "/enc_dec.txt");
	append_to_file(pth, buf);

	/*add one client*/
	element_t ns;
	element_t npp;
	dk *nc = malloc(sizeof(dk) * num_client);

	// benchamark adding one more client
	time1 = pbc_get_time();
	waters_keysetup(pp, ns, npp);
	// verification

	element_t nT;
	element_t ncc;
	element_t nw;

	if (verification_flag == 1)
	{
		zk_proof(ns, pp->g, npp, nT, ncc, nw, pp->pairing);
	}
	/*the trusted repository server computation BEGIN*/

	if (verification_flag == 1)
	{
		int t = waters_pkVerify(nw, nT, ncc, pp->g, npp, pp->pairing);
		if (t != 0)
		{
			element_printf("pkVerify fails\n");
		}
	}

	for (int i = 0; i < num_client; i++)
	{
		waters_keyder(nc[i], pp, ns, i + 1);
	}

	/*the trusted repository server computation BEGIN */
	waters_pCombine(g1, g1, npp);
	/*the trusted repository server computation END */

	int c_id = 123456; // let the new client has id = 123456
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

	if (verification_flag == 1)
	{
		for (int i = 0; i < num_client; i++)
		{
			if (waters_dkVerify(pp, npp, i + 1, nc[i]) != 0)
			{
				printf(" dkVerify fail \n");
			}
			if (waters_dkVerify(pp, clients_g1[i], c_id, cd[i]) != 0)
			{
				printf("dkVerify fail \n");
			}
		}
	}

	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	strcpy(pth + strlen(dir), "/addClient.txt");
	append_to_file(pth, buf);

	// FOR DEBUG
	if (waters_dkVerify(pp, g1, c_id, ncd) != 0)
	{
		printf("dkVerify fail\n");
	}

	if (waters_enc_dec(pp, g1, c_id, ncd) != 0)
	{
		printf("decryption fails\n");
	}


	for (int i = 0; i < num_client; i++)
	{
		element_clear(nc[i][0]);
		element_clear(nc[i][1]);
		element_clear(clients_sk[i]);
		element_clear(clients_g1[i]);
		element_clear(Tptr[i]);
		element_clear(cptr[i]);
		element_clear(wptr[i]);
		element_clear(decryption_keys[i][0]);
		element_clear(decryption_keys[i][1]);
		element_clear(cd[i][0]);
		element_clear(cd[i][1]);
	}
	free(nc);
	free(clients_sk);
	free(clients_g1);

	free(Tptr);
	free(cptr);
	free(wptr);

	free(decryption_keys);
	free(cd);

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
	element_clear(g1);
	element_clear(ns);
	element_clear(npp);
	if (verification_flag == 1)
	{
		element_clear(nT);
		element_clear(ncc);
		element_clear(nw);
	}

	element_clear(ncd[0]);
	element_clear(ncd[1]);
}

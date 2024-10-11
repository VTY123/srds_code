#include "./sim_ns_ibe.h"

void sim_ns_ibe(pp pp, int num_client,char* dir)
{
	char pth[128];
	strcpy(pth,dir);
	char buf[128];
	// initialize receivers' variables of secret keys and related public parameters
	element_t *clients_sk = malloc(sizeof(element_t) * num_client);
	element_t *clients_g1 = malloc(sizeof(element_t) * num_client);

	double time1, time2;
	// benchmark keysetup
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		waters_keysetup(pp, clients_sk[i], clients_g1[i]);
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	strcpy(pth+strlen(dir),"/keysetup.txt");
	append_to_file(pth, buf);


	// initialize reecivers' variables of decryption key contributions
	dk **clients_dks = malloc(sizeof(dk *) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		clients_dks[i] = malloc(sizeof(dk) * num_client);
	}
	// benchmark keyder
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		// clients_dks[i] = malloc(sizeof(dk) * num_client);
		for (int id = 1; id <= num_client; id++)
		{
			waters_keyder(clients_dks[i][id - 1], pp, clients_sk[i], id);
		}
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	strcpy(pth+strlen(dir),"/keyder.txt");
	append_to_file(pth, buf);

	// benchmark the simulation about receivers run pCombine
	element_t *clients_cpp = malloc(sizeof(element_t) * num_client);
	time1 = pbc_get_time();
	for (int i = 0; i < num_client; i++)
	{
		element_init_G1(clients_cpp[i], pp->pairing);
		element_set0(clients_cpp[i]);
		for (int j = 0; j < num_client; j++)
		{
			waters_pCombine(clients_cpp[i], clients_cpp[i], clients_g1[j]);
		}
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	strcpy(pth+strlen(dir),"/pCombine.txt");
	append_to_file(pth, buf);

	// initalize receivers' variables of decryption keys
	dk *decryption_keys = malloc(sizeof(dk) * (num_client));

	// benchmark kCombine
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
	strcpy(pth+strlen(dir),"/kCombine.txt");
	append_to_file(pth, buf);	

	// verify decryption correctness
	for (int i = 0; i < num_client; i++)
	{
		int r = waters_enc_dec(pp, clients_cpp[i], i + 1, decryption_keys[i]);
		if (r != 0)
		{
			printf("enc dec fail\n");
		}
	}

	/*add one client*/
	element_t ns;
	element_t npp;
	dk *nc = malloc(sizeof(dk) * num_client);
	time1 = pbc_get_time();
	waters_keysetup(pp, ns, npp);

	// no verification for adding a client for this protocol
	for (int i = 0; i < num_client; i++)
	{
		waters_keyder(nc[i], pp, ns, i + 1);
	}

	int c_id = 123456; // an example id for the new client
	// pCombine is computed by clients
	dk *cd = malloc(sizeof(dk) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		waters_pCombine(clients_cpp[i], clients_cpp[i], npp);
		waters_kCombine(decryption_keys[i], decryption_keys[i], nc[i]);
		waters_keyder(cd[i], pp, clients_sk[i], c_id);
	}

	dk ncd;
	waters_keyder(ncd, pp, ns, c_id);
	for (int i = 0; i < num_client; i++)
	{
		waters_kCombine(ncd, ncd, cd[i]);
		waters_pCombine(npp, npp, clients_g1[i]);
	}

	time2 = pbc_get_time();
	sprintf(buf, "%d,%f", num_client, time2 - time1);
	strcpy(pth+strlen(dir),"/addClient.txt");
	append_to_file(pth, buf);	

	// DEBUG: test for the decryption correctness
	int r = waters_enc_dec(pp, npp, c_id, ncd);
	if (r != 0)
	{
		printf("enc dec fail\n");
	}

	/* clean up code */
	//
	element_clear(ns);
	element_clear(npp);
	for (int i = 0; i < num_client; i++)
	{
		element_clear(nc[i][0]);
		element_clear(nc[i][1]);
		element_clear(cd[i][0]);
		element_clear(cd[i][1]);
		element_clear(clients_sk[i]);
		element_clear(clients_g1[i]);
		element_clear(decryption_keys[i][0]);
		element_clear(decryption_keys[i][1]);
		element_clear(clients_cpp[i]);
	}
	free(nc);
	free(cd);
	free(clients_sk);
	free(clients_g1);
	free(decryption_keys);
	free(clients_cpp);

	element_clear(ncd[0]);
	element_clear(ncd[1]);

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

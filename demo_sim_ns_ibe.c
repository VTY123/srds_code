#include "./demo_sim_ns_ibe.h"

void demo_ns_ibe(public_parameters pp, int num_client, char *dir)
{
	char pth[128];
	strcpy(pth, dir);
	//char buf[128];
	// secret keys and related public parameters for users
	element_t *clients_sk = malloc(sizeof(element_t) * num_client);
	element_t *clients_g1 = malloc(sizeof(element_t) * num_client);

	for (int i = 0; i < num_client; i++)
	{
		waters_keysetup(pp, clients_sk[i], clients_g1[i]);
		element_printf("the %d-th user runs key setup algorithm\n", i);
	}

	// decryption keys
	dk **clients_dks = malloc(sizeof(dk *) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		clients_dks[i] = malloc(sizeof(dk) * num_client);
	}

	// benchmark keyder
	for (int i = 0; i < num_client; i++)
	{
		// clients_dks[i] = malloc(sizeof(dk) * num_client);
		for (int id = 1; id <= num_client; id++)
		{
			waters_keyder(clients_dks[i][id - 1], pp, clients_sk[i], id);
			element_printf("the %d-th user derives key for the %d-th user\n", i, id);
		}
	}

	element_printf("users exchanges for contributions to public parameters and decryption keys\n");

	// benchmark the simulation about receivers run pCombine
	element_t *clients_cpp = malloc(sizeof(element_t) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		element_init_G1(clients_cpp[i], pp->pairing);
		element_set0(clients_cpp[i]);
		for (int j = 0; j < num_client; j++)
		{
			element_printf("the %d-th user combines the constribution to public parameter from the %d-th user\n", i, j);
			waters_pCombine(clients_cpp[i], clients_cpp[i], clients_g1[j]);
		}
	}

	//	append_to_file(pth, buf);

	// initalize receivers' variables of decryption keys
	dk *decryption_keys = malloc(sizeof(dk) * (num_client));

	// benchmark kCombine
	for (int i = 0; i < num_client; i++)
	{
		element_init_G1(decryption_keys[i][0], pp->pairing);
		element_init_G1(decryption_keys[i][1], pp->pairing);
		element_set(decryption_keys[i][0], clients_dks[0][i][0]);
		element_set(decryption_keys[i][1], clients_dks[0][i][1]);
		for (int j = 1; j < num_client; j++)
		{
			element_printf("the %d-th user combine the constribution to decryption key from the %d-th user\n", i, j);
			waters_kCombine(decryption_keys[i], decryption_keys[i], clients_dks[j][i]);
		}
	}

	element_t M;
	element_init_GT(M, pp->pairing);
	unsigned char *str = calloc(1, element_length_in_bytes(M));
	// element_printf(" sz = %d\n",)
	strcpy((char *)str, "hello");

	element_from_bytes(M, str);

	ct CT;
	for (int test_id = 1; test_id <= num_client; test_id++)
	{
		waters_enc(CT, pp, clients_cpp[test_id - 1], test_id, M);
		element_t DM;
		waters_dec(DM, pp, CT, decryption_keys[test_id - 1]);

		element_to_bytes(str, DM);

		element_printf(" decrypted message is %s\n", str);
	}

	/* clean up code */

	for (int i = 0; i < num_client; i++)
	{

		element_clear(clients_sk[i]);
		element_clear(clients_g1[i]);
		element_clear(decryption_keys[i][0]);
		element_clear(decryption_keys[i][1]);
		element_clear(clients_cpp[i]);
	}

	free(clients_sk);
	free(clients_g1);
	free(decryption_keys);
	free(clients_cpp);

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

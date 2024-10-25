#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"
#include "./sim_ns_ibe.h"

// simulating the ns-IBE

//benchmark data is stored in the directory ./ns_ibe_addClient_data

int main(int argc, char **argv)
{
	public_parameters pp = malloc(sizeof(struct public_parameters));
	pbc_demo_pairing_init(pp->pairing, argc, argv);
	waters_commonsetup(pp);

	int arr[11] = {0};

	arr[0] = 1;
	for (int i = 1; i < 11; i++)
	{
		arr[i] = i * 100;
	}
	for (int k = 0; k < 11; k++)
	{
		sim_ns_ibe(pp, arr[k],"ns_ibe_addClient_data");
	}
	free(pp);
}

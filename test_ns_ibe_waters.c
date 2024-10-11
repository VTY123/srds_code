#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"
#include "./sim_ns_ibe.h"

//benchmark data is stored in the directory ./ns_ibe_data

int main(int argc, char **argv)
{
	pp pp = malloc(sizeof(struct public_parameters));
	pbc_demo_pairing_init(pp->pairing, argc, argv);
	waters_commonsetup(pp);
	int arr[3] = {0};
	arr[0] = 200;
	arr[1] = 600;
	arr[2] = 1000;;
	for (int k = 0; k < 3; k++)
	{
		sim_ns_ibe(pp, arr[k],"ns_ibe_data");
	}
	free(pp);
}

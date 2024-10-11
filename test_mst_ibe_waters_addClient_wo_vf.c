#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"
#include "./sim_mst_ibe.h"
//simulating the mst-ibe

//benchmark data is stored in the directory ./mst_ibe_addClient_data


int main(int argc, char **argv)
{
	pp pp = malloc(sizeof(struct public_parameters));
	pbc_demo_pairing_init(pp->pairing, argc, argv);
	waters_commonsetup(pp);

	int arr[11] = {0};
	arr[0] = 1;
	for (int i = 1; i <= 10;i++){
		arr[i] = i*100;
	}

	for (int k = 0; k < 11; k++)
	{
		//without verification
		sim_mst_ibe(pp, arr[k], 0,"mst_ibe_addClient_wo_vf_data");
	}
	free(pp);
}

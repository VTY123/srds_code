#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"
#include "./demo_sim_ns_ibe.h"

//benchmark data is stored in the directory ./ns_ibe_data

int main(int argc, char **argv)
{
	public_parameters pp = malloc(sizeof(struct public_parameters));
	pbc_demo_pairing_init(pp->pairing, argc, argv);
	waters_commonsetup(pp);

	demo_ns_ibe(pp, 3,"ns_ibe_data");
	
	free(pp);
}

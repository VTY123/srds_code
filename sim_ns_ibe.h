#ifndef SIM_NS_IBE
#define SIM_NS_IBE

#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"

//simulate ns-IBE based on Waters IBE

// simulation runs follows: at the beginning, one of receivers runs CommonSetup->

// all receivers run the rest of the protocol: keysetup->keyder->pcombine->kcombine

//FOR DEBUG: run enc and dec algorithms to verify decryption correctness

//benchmark keysetup,keyder,pcombine,kcombine

//pulse: simulate and bench mark add one more client

// We separate the computation of key derivation
// and the computation of the kCombine for benchmark and observation.


/*
	Highlight the trusted repository server computation
*/


void sim_ns_ibe(public_parameters pp, int num_client,char* dir);

#endif

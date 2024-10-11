
#ifndef SIM_MST_IBE
#define SIM_MST_IBE

#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./waters_ibe.h"
#include "./file_process.h"

// simulate the mst-ibe based on Waters IBE

// simulation assumes following running sequence:
// server runs CommonSetup -> all clients run KeySetup -> server runs pkVerify
// all clients run KeyDer -> server runs dkVerify ->server runs pCombine ->  server runs kCombine

// FOR DEBUG: run enc and dec algorithms to verifying the decryption correctness

// pulse simulating add one more client

// We separate the computation of key derivation
// and the computation of the kCombine for benchmark and observation.

void sim_mst_ibe(pp pp, int num_client, int verification_flag, char* dir);

#endif

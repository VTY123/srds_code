#include <pbc.h>
#include <pbc_test.h>
#include <string.h>
#include "./file_process.h"
#include "./waters_ibe.h"


// this code focus on benchmarks of keyder and dkVerify with multi-threads

typedef struct thread_dkVerify_arg
{
	struct public_parameters *pp;
	element_t *g1ptr;
	int *ids;
	dk *d;
	int *results;
	int pass; //if one of results is invalid, then it is not pass
	int len;
} thread_dkVerify_arg;

void *th_dkVerify(void *args)
{
	thread_dkVerify_arg *arg = (thread_dkVerify_arg *)args;
	arg->pass = 0;
	for (int i = 0; i < arg->len; i++)
	{
		int r = waters_dkVerify(arg->pp, *arg->g1ptr, arg->ids[i], arg->d[i]);
		arg->results[i] = r;
		if (r != 0){
			arg->pass = -1;
		}
	}
	return NULL;
}

void *th_enc_dec(void *args)
{    /*enc dec for testing*/
	thread_dkVerify_arg *arg = (thread_dkVerify_arg *)args;
	arg->pass = 0;
	for (int i = 0; i < arg->len; i++)
	{
		int r = waters_enc_dec(arg->pp, *arg->g1ptr, arg->ids[i], arg->d[i]);
		if (r != 0){
			arg->pass = -1;
		}
		arg->results[i] = r;
	}
	return NULL;
}

typedef struct thread_keyder_arg
{
	struct public_parameters *pp;
	element_t *sk;
	int *ids;
	dk *d;
	int len;
} thread_keyder_arg;

void *th_keyder(void *args)
{
	thread_keyder_arg *arg = (thread_keyder_arg *)args;
	for (int i = 0; i < arg->len; i++)
	{
		waters_keyder(arg->d[i], arg->pp, *arg->sk, arg->ids[i]);
	}
	return NULL;
}

void sim_parallel(public_parameters pp, int num_thread, int num_client)
{
//num_thread is the number of threads WILL BE CREATED.
//so total number of threads is num_thread + 1.

	//initialize variables of secret keys and their related public parameters 
	element_t *g1ptr = malloc(sizeof(element_t));
	element_t *sk_ptr = malloc(sizeof(element_t));
	
	//
	waters_keysetup(pp, *sk_ptr, *g1ptr);
	int *ids = malloc(sizeof(int) * num_client);
	for (int i = 0; i < num_client; i++)
	{
		ids[i] = i+1;
	}

	double time1, time2;
	pthread_t *threads = malloc(sizeof(pthread_t) * num_thread);
	int load_per_thread = num_client / (num_thread + 1);
	thread_keyder_arg **keyder_argptr = malloc(sizeof(thread_keyder_arg *) * num_thread);
	dk *clients_dk = malloc(num_client * sizeof(dk));

	for (int i = 0; i < num_thread; i++)
	{
		keyder_argptr[i] = malloc(sizeof(thread_keyder_arg));
		keyder_argptr[i]->len = load_per_thread;
		keyder_argptr[i]->pp = pp;
		keyder_argptr[i]->sk = sk_ptr;
		keyder_argptr[i]->d = clients_dk + load_per_thread * i;
		keyder_argptr[i]->ids = ids + load_per_thread*i; 
	}

	time1 = pbc_get_time();
	for (int i = 0; i < num_thread; i++)
	{	
		pthread_create(&threads[i], NULL, th_keyder, (void *)keyder_argptr[i]);
	}
	// main thread also handles remainder load.

	for (int i = num_thread * load_per_thread; i < num_client; i++)
	{
		waters_keyder(clients_dk[i], pp, *sk_ptr, i);
	}

	for (int i = 0; i < num_thread; i++)
	{
		pthread_join(threads[i], NULL);
		free(keyder_argptr[i]);
	}
	time2 = pbc_get_time();

	free(keyder_argptr);

	char buf[128];
	sprintf(buf, "%d,%d,%f", num_thread + 1, num_client, time2 - time1);
	append_to_file("multithreads_data/keyder_parallel.txt", buf);

	thread_dkVerify_arg ** dkVerify_args = malloc(sizeof(thread_dkVerify_arg *) * num_thread);
	for (int i = 0; i < num_thread; i++)
	{
		dkVerify_args[i] = malloc(sizeof(thread_dkVerify_arg));
		dkVerify_args[i]->len = load_per_thread;
		dkVerify_args[i]->pp = pp;
		dkVerify_args[i]->g1ptr = g1ptr;
		dkVerify_args[i]->ids = ids + i * load_per_thread;
		dkVerify_args[i]->results = malloc(sizeof(int) * load_per_thread);
		dkVerify_args[i]->d = clients_dk + i * load_per_thread;
	}

	time1 = pbc_get_time();
	for (int i = 0; i < num_thread; i++)
	{
		pthread_create(&threads[i], NULL, th_dkVerify, (void *)dkVerify_args[i]);
	}

	for (int i = num_thread * load_per_thread; i < num_client; i++)
	{
		int r = waters_dkVerify(pp, *g1ptr, i, clients_dk[i]);
		if (r != 0){
			printf("dkVerify fails\n");
		}
	}

	for (int i = 0; i < num_thread; i++)
	{
		pthread_join(threads[i], NULL);
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%d,%f", num_thread + 1, num_client, time2 - time1);
	append_to_file("multithreads_data/dkVerify_parallel.txt", buf);

	for (int i = 0; i < num_thread; i++)
	{
		if (dkVerify_args[i]->pass != 0){
			printf("dkVerify fails\n");
		}
		//free(dkVerify_args[i]->results);
	}

	//multi-thread enc and dec are not used for the project
	time1 = pbc_get_time();
	for (int i = 0; i < num_thread; i++)
	{	
		pthread_create(&threads[i], NULL, th_enc_dec, (void *)dkVerify_args[i]);
	}
	for (int i = num_thread * load_per_thread; i < num_client; i++)
	{
		int r  = waters_enc_dec(pp, *g1ptr, i, clients_dk[i]);
		if (r != 0){
			printf("enc dec fails\n");
		}
	}
	for (int i = 0; i < num_thread; i++)
	{
		pthread_join(threads[i], NULL);
	}
	time2 = pbc_get_time();
	sprintf(buf, "%d,%d,%f", num_thread + 1, num_client, time2 - time1);
	append_to_file("multithreads_data/enc_dec_parallel.txt", buf);

	for (int i = 0; i < num_thread; i++)
	{
		if (dkVerify_args[i]->pass != 0){
			printf("enc dec fails\n");
		}
		free(dkVerify_args[i]->results);
		free(dkVerify_args[i]);
	}
	free(dkVerify_args);

	for (int i = 0; i < num_client;i++){
		element_clear(clients_dk[i][0]);
		element_clear(clients_dk[i][1]);
	}
	free(clients_dk);
	element_clear(*sk_ptr);
	free(sk_ptr);
	free(threads);
}

int main(int argc, char **argv)
{
	public_parameters pp = malloc(sizeof(struct public_parameters));        
	pbc_demo_pairing_init(pp->pairing, argc, argv);
	waters_commonsetup(pp);
	for (int j = 100; j <= 1000; j += 100)
	{
		for (int i = 1; i < 5; i = i *2)
		{
			sim_parallel(pp, i-1, j);
		}
	}
	waters_clear_pp(pp);
	free(pp);
}

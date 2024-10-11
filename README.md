
This source code is for the SRDS paper. In other words, it is for prototyping and simulation only.


Some code for backup or prototype: test

Github link:


##Installation
Download and install the pbc library
https://crypto.stanford.edu/pbc/download.html

 Make sure example code can be run.


##How to compile codes and create environment  for simulation 

A simple approach:  delete all files in the example folder. Add all our files to it. 

A detailed approach:

1. Copy following to the example folder
waters_ibe.c,waters_ibe.h,sim
test_ns_ibe.c ,test_mst_ibe.c
sim_ns_ibe.c, sim_mst_ibe.c
test.sh

2. Create directories
ns_ibe_data
ns_ibe_addClient_data
mst_ibe_data
mst_ibe_data_addClient_w_vf_data
mst_ibe_data_addClient_wo_vf_data
multithreads_data

3. Add following to the Makefile.am
Add following to noinst_PROGRAMS variable: test_ns_ibe_waters test_ns_ibe_waters_addClient test_mst_ibe_waters test_mst_ibe_addClient_wo_vf test_mst_ibe_addClient_w_vf test_waters_multithreads

add: test_waters_multithreads_SOURCES = waters_ibe.h waters_ibe.c test_waters_threads_keyder.c file_process.c
Add: test_ns_ibe_waters_SOURCES = test_ns_ibe_waters.c sim_ns_ibe.c waters_ibe.h waters_ibe.c file_process.c

add following:test_mst_ibe_waters_SOURCES = test_mst_ibe_waters.c  sim_mst_ibe.c waters_ibe.h waters_ibe.c  file_process.c

add: test_ns_ibe_waters_addClient_SOURCES = test_ns_ibe_waters_addClient.c sim_ns_ibe.c waters_ibe.h waters_ibe.c file_process.c
test_mst_ibe_addClient_wo_vf_SOURCES = test_mst_ibe_waters_addClient_wo_vf.c sim_mst_ibe.c waters_ibe.h waters_ibe.c file_process.c
test_mst_ibe_addClient_w_vf_SOURCES = test_mst_ibe_waters_addClient_w_vf.c sim_mst_ibe.c  waters_ibe.h waters_ibe.c file_process.c

##How to run the code

It is like other examples in PBC library. 

Command: ./test_ns_ibe_waters ../param/a.param




##How to plot the data
Run the bash script test.sh for simulation
To plot the data, run with python scripts as follows
python3 python_scripts/plt_ns_ibe.py
Plot the data of ns-ibe
python3 python_scripts/plt_mst_ibe.py
Plot the data of mst-ibe
python3 python_scripts/plt_addclient.py
Plot the data of 
python3 python_scripts/plt_multithread_waters.py
Plot 




How to modify the software code for various simulations

We can add or remove the verification part of simulation by uncomment/comment related parts of codes. 


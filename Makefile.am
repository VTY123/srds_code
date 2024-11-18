CLEANFILES = *~
maintainer-clean-local:
	-rm -rf Makefile.in

   
AM_CPPFLAGS = -I../include
LDADD = ../libpbc.la -lgmp


noinst_PROGRAMS = demo_mst_ibe demo_ns_ibe test_ns_ibe_waters test_ns_ibe_waters_addClient test_mst_ibe_waters test_mst_ibe_addClient_wo_vf test_mst_ibe_addClient_w_vf test_waters_multithreads 

demo_mst_ibe_SOURCES = demo_mst_ibe.c waters_ibe.h waters_ibe.c demo_sim_mst_ibe.c file_process.c

demo_ns_ibe_SOURCES = demo_ns_ibe.c waters_ibe.h waters_ibe.c demo_sim_ns_ibe.c file_process.c

test_waters_multithreads_SOURCES = waters_ibe.h waters_ibe.c test_waters_threads_keyder.c file_process.c

test_ns_ibe_waters_SOURCES = test_ns_ibe_waters.c  sim_ns_ibe.c  waters_ibe.c file_process.c

test_mst_ibe_waters_SOURCES = test_mst_ibe_waters.c  sim_mst_ibe.c waters_ibe.h waters_ibe.c  file_process.c

test_ns_ibe_waters_addClient_SOURCES = test_ns_ibe_waters_addClient.c sim_ns_ibe.c waters_ibe.h waters_ibe.c file_process.c

test_mst_ibe_addClient_wo_vf_SOURCES = test_mst_ibe_waters_addClient_wo_vf.c sim_mst_ibe.c waters_ibe.h waters_ibe.c file_process.c

test_mst_ibe_addClient_w_vf_SOURCES = test_mst_ibe_waters_addClient_w_vf.c sim_mst_ibe.c  waters_ibe.h waters_ibe.c file_process.c

test_waters_singlethread_SOURCES = waters_ibe.h waters_ibe.c test_waters_ibe.c file_process.c

test_waters_singlethread_c_SOURCES = waters_ibe.h waters_ibe.c test_waters_ibe_c.c file_process.c



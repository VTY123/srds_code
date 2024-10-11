from pprint import pprint
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
import numpy as np
import matplotlib
matplotlib.rc('xtick',labelsize=20)
matplotlib.rc('ytick',labelsize=20)

def get_ns_ibe(filename):
	f = open('./ns_ibe_addClient_data/'+filename,'r')
	s = f.read()
	arr = s.split('\n')
	arr = arr[0:-1]
	xa = []
	ya = []
	for i in range(len(arr)):
		t = arr[i].split(',')
		xa.append(float(t[0]))
		ya.append(float(t[1]))
	
	return [np.array(xa),np.array(ya)]

def get_mst_ibe_wo_vf(filename):
	f = open('./mst_ibe_addClient_wo_vf_data/'+filename,'r')
	s = f.read()
	arr = s.split('\n')
	arr = arr[0:-1]
	xa = []
	ya = []
	for i in range(len(arr)):
		t = arr[i].split(',')
		xa.append(float(t[0]))
		ya.append(float(t[1]))
	
	return [np.array(xa),np.array(ya)]


def get_mst_ibe_w_vf(filename):
	f = open('./mst_ibe_addClient_w_vf_data/'+filename,'r')
	s = f.read()
	arr = s.split('\n')
	arr = arr[0:-1]
	xa = []
	ya = []
	for i in range(len(arr)):
		t = arr[i].split(',')
		xa.append(float(t[0]))
		ya.append(float(t[1]))
	
	return [np.array(xa),np.array(ya)]

def acc(arr1,arr2):
	r = []
	for i in range(len(arr1)):
		r.append(arr1[i]+arr2[i])
	return r

def get_ns_ibe_acc():
	#for calculating trend lines
	i = [0,1,2,3,4,5,6,7,8,9,10]
	keysetupdata = get_ns_ibe('keysetup.txt')
	keyderdata = get_ns_ibe('keyder.txt')
	pCombinedata = get_ns_ibe('pCombine.txt')
	kCombinedata = get_ns_ibe('kCombine.txt')
	r = acc(keysetupdata[1][i],keyderdata[1][i])
	r = acc(r,pCombinedata[1][i])
	r = acc(r,kCombinedata[1][i])
	print("ns ibe =")
	#print(r)
	for i in r:
		print(i)
	return 


def get_mst_ibe_w_vf_acc():
	#for calculating trend lines
	i = [0,1,2,3,4,5,6,7,8,9,10]
	keysetupdata = get_mst_ibe_wo_vf('keysetup.txt')
	keyderdata = get_mst_ibe_wo_vf('keyder.txt')
	pCombinedata = get_mst_ibe_wo_vf('pCombine.txt')
	kCombinedata = get_mst_ibe_wo_vf('kCombine.txt')
	pkVerifydata = get_mst_ibe_wo_vf('pkVerify.txt')
	dkVerifydata = get_mst_ibe_wo_vf('dkVerify.txt')
	r = acc(keysetupdata[1][i],keyderdata[1][i])
	r = acc(r,pCombinedata[1][i])
	r = acc(r,kCombinedata[1][i])
	#r = acc(r,pkVerifydata[1][i])
	#r = acc(r,dkVerifydata[1][i])
	print('mst ibe = ')
	#print(str(r)+',')
	for i in r:
		print(str(i)+',')
	return 

get_ns_ibe_acc()
get_mst_ibe_w_vf_acc()

plt.figure(figsize=(8,5))

addclientdata = get_ns_ibe('addClient.txt')
print('ns-ibe add clients')
#print(addclientdata[1])
for i in addclientdata[1]:
	print(i)

plt.plot(addclientdata[0],addclientdata[1],'x',color = plt.cm.Greys(1.0), label = 'ns-ibe')

addclientdata = get_mst_ibe_wo_vf('addClient.txt')
print('mst ibe add Clients wo')
for i in addclientdata[1]:
	print(i)
#print(addclientdata)
plt.plot(addclientdata[0],addclientdata[1],color = plt.cm.Greys(1.0), label = 'mst-ibe w/o verification',linestyle='dashed')
print('mst ibe add Clients')
print(addclientdata[1])

addclientdata = get_mst_ibe_w_vf('addClient.txt')
plt.plot(addclientdata[0],addclientdata[1],'-',color = plt.cm.Greys(1.0), label = 'mst-ibe w verification')
print('mst ibe add Client with vf')
for i in addclientdata[1]:
	print(i)
plt.subplots_adjust(left= 0.10,right=0.95,top=0.95,bottom=0.15)
plt.xlim((50,1050))
plt.ylim(0)
plt.xlabel('Number of Current Users',fontsize=20)
plt.ylabel('Time(s)',fontsize=20)
plt.legend(fontsize=18,loc="upper left")

plt.show()

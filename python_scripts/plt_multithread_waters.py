from pprint import pprint
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
import matplotlib
matplotlib.rc('xtick',labelsize=20)
matplotlib.rc('ytick',labelsize=20)

#This script is used for ploting the multi-thread simulation
				
def plot_dkVerify():
	arg_label = 'dkVerify'
	arg_linestyle = '--'
	f = open('./multithreads_data/dkVerify_parallel.txt','r')
	s = f.read()
	arr = s.split('\n')
	arr = arr[0:-1]
	max_thread = 4
	xa = []
	ya = []
	for i in range(max_thread):
		xa.append([])
		ya.append([])

	ta = []
	pt = []
	for i in range(len(arr)):
		t = arr[i].split(',')
		ta.append(int(t[0]))
		xa[ta[i]-1].append(float(t[1]))
		ya[ta[i]-1].append(float(t[2]))

	for i in range(4):
		if i == 0:
			plt.plot(xa[i],ya[i],label = arg_label + ' ' + (i+1).__str__() + ' thread',marker = '*',color= plt.cm.Greys(1.0),linestyle = arg_linestyle)
		elif xa[i]: 
			if i == 1:
				plt.plot(xa[i],ya[i],label = arg_label + ' ' + (i+1).__str__() + ' threads',marker = 'p',color= plt.cm.Greys(1.0),linestyle = arg_linestyle)
			elif i == 3:
				plt.plot(xa[i],ya[i],label = arg_label + ' ' + (i+1).__str__() + ' threads',marker = 'X',color= plt.cm.Greys(1.0),linestyle = arg_linestyle)

def plot_keyder():
	arg_label = 'keyder'
	arg_linestyle = '-'
	f = open('./multithreads_data/keyder_parallel.txt','r')
	s = f.read()
	arr = s.split('\n')
	arr = arr[0:-1]
	max_thread = 4
	xa = []
	ya = []
	for i in range(max_thread):
		xa.append([])
		ya.append([])

	ta = []
	pt = []
	for i in range(len(arr)):
		t = arr[i].split(',')
		ta.append(int(t[0]))
		xa[ta[i]-1].append(float(t[1]))
		ya[ta[i]-1].append(float(t[2]))

	for i in range(4):
		if i == 0:
			plt.plot(xa[i],ya[i],label = arg_label + ' ' + (i+1).__str__() + ' thread',marker = '<',color= plt.cm.Greys(1.0),linestyle = arg_linestyle)
		elif xa[i]: 
			if i == 1:
				plt.plot(xa[i],ya[i],label = arg_label + ' ' + (i+1).__str__() + ' threads',marker = 'v',color= plt.cm.Greys(1.0),linestyle = arg_linestyle)
			elif i == 3:
				plt.plot(xa[i],ya[i],label = arg_label + ' ' + (i+1).__str__() + ' threads',marker = '^',color= plt.cm.Greys(1.0),linestyle = arg_linestyle)
				

plt.figure(figsize=(8,5))
plot_dkVerify()
plot_keyder()
plt.subplots_adjust(left= 0.15,right=0.95,top=0.95,bottom=0.15)
plt.xlim((50,1050))
plt.ylim(0,3)
plt.xlabel('Number of Keys',fontsize=20)
plt.ylabel('Time(s)',fontsize=20)

#plt.legend(loc="upper left",bbox_to_anchor=(-0.2, 1.4),fancybox=True, shadow=True,ncol = 2,fontsize=18)
plt.legend(loc="upper left",bbox_to_anchor=(-0.01,1.02),ncol = 2,fontsize=17)
plt.show()

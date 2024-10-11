import matplotlib.pyplot as plt
import matplotlib
import numpy as np

matplotlib.rc('xtick',labelsize=20)
matplotlib.rc('ytick',labelsize=20)

DIR='.'

def get_watersdata(filename):
	f = open(DIR+'/ns_ibe_data/'+filename,'r')
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

def bar_acc():
	i = [1,2,3]
	keysetupdata = get_watersdata('keysetup.txt')
	keyderdata = get_watersdata('keyder.txt')
	pCombinedata = get_watersdata('pCombine.txt')
	kCombinedata = get_watersdata('kCombine.txt')
	r = acc(keysetupdata[1][i],keyderdata[1][i])
	r = acc(r,pCombinedata[1][i])
	r = acc(r,kCombinedata[1][i])
	#r = acc(r,kCombineserverdata[1][i])
	#r = acc(r,zkclientdata[1])
	print(r)

	return 


def bar_plot():
	barWidth = 0.15
	br = np.arange(3)
	for i in range(len(br)):
		br[i] = br[i] + 3*barWidth

	br1 = [x + barWidth for x in br]
	br2 = [x + barWidth for x in br1]
	br3 = [x + barWidth for x in br2]
	br4 = [x + barWidth for x in br3]
	br5 = [x + barWidth for x in br4]

	wbr1 = [ x + 5*barWidth for x in br]
	wbr2 = [ x + barWidth for x in wbr1]
	wbr3 = [ x + barWidth for x in wbr2]
	wbr4 = [ x + barWidth for x in wbr3]


	i = [0,1,2]
	#i = [2,4,6,8,10]
	keysetupdata = get_watersdata('keysetup.txt')
	keyderdata = get_watersdata('keyder.txt')
	pCombinedata = get_watersdata('pCombine.txt')

	#plt.bar(br,zkclientdata[1][i]+ keysetupdata[1][i],width=barWidth,label='KeySetup', edgecolor = plt.cm.Greys(1.0),color= plt.cm.Greys(1.0),linestyle='-')
	plt.bar(br1,keysetupdata[1][i],width=barWidth,label='KeySetup',fill = True ,color= plt.cm.Greys(1.0))
	plt.bar(br2,keyderdata[1][i],width=barWidth,label='KeyDer',fill = False ,color= plt.cm.Greys(1.0))
	plt.bar(br3,pCombinedata[1][i],width=barWidth,label='pCombine',color= plt.cm.Greys(.6))
	
	kCombinedata = get_watersdata('kCombine.txt')
	#kCombineclientdata = get_watersdata('kCombine_client.txt')

	#plt.bar(br3,kCombineserverdata[1][i],width=barWidth,label='kCombine',edgecolor = plt.cm.Greys(1.0),color= plt.cm.Greys(.3))


	#plt.bar(br4,kCombineclientdata[1][i],width=barWidth,label='kCombine',edgecolor = plt.cm.Greys(1.0),color= plt.cm.Greys(.3))


	plt.bar(br4,kCombinedata[1][i],width=barWidth,label='kCombine',color= plt.cm.Greys(.3))	


	r = acc(keyderdata[1],keysetupdata[1])
	r = acc(r,pCombinedata[1])
	#r = acc(r,kCombineclientdata[1]+kCombineserverdata[1])
	#r = acc(r,zkclientdata[1]+zkserverdata[1])
	#r = acc(r,zkclientdata[1])
	#r = acc(r,testkeydata[1])

	for k in r:
		print('k1 = ')
		print(k)


	#keysetupdata = get_watersdata('keysetup.txt')
	#plt.bar(wbr1,keysetupdata[1][i],width=barWidth,label='KeySetup (Waters)',hatch='//', edgecolor = plt.cm.Greys(1.0), color= plt.cm.Greys(.0))
	
	#keyderdata = get_watersdata('keyder.txt')
	#plt.bar(wbr2,keyderdata[1][i],width=barWidth,label='KeyDer (Waters)',hatch = '//',color= plt.cm.Greys(.3))
	
	#pCombinedata = get_watersdata('pCombine.txt')
	#plt.bar(wbr3,pCombinedata[1][i],width=barWidth,label='pCombine (Waters)',hatch='//', edgecolor = plt.cm.Greys(1.0),color = plt.cm.Greys(.6))

#	kCombinedata = get_watersdata('kCombine.txt')
#	plt.bar(wbr4,kCombinedata[1][i],width=barWidth,label='kCombine (Waters)',hatch='\\\\', edgecolor = plt.cm.Greys(1.0),color = plt.cm.Greys(0.0))

#	r = acc(keyderdata[1],keysetupdata[1])
#	r = acc(r,pCombinedata[1])
#	r = acc(r,kCombinedata[1])

#	for k in r:
#		print('k2 = ')
#		print(k)




	xbr = br1#+wbr2
	xbr = [x + barWidth/2 for x in xbr] 
	ystr = [str(int(keysetupdata[0][x])) for x in i] #+ [str(int(keysetupdata[0][x]))+' clients (Waters)' for x in i] 
	
	plt.xticks(xbr,ystr)
	#plt.xticks(br1,[str(int(keysetupdata[0][x]))+' clients (BF)' for x in range(0,10,3)],rotation=-45)
	#plt.xticks(wbr2,[str(int(keysetupdata[0][x]))+' clients (Waters)' for x in range(0,10,3)],rotation=-45)




plt.figure(figsize=(12,5))
bar_plot()
#bar_acc()
plt.subplots_adjust(left= 0.1,right=0.95,top=0.95,bottom=0.15)
#plt.xlim((50,1050))
#plt.xlabel('Number of Clients',fontsize=15)
plt.ylabel('Time(s)',fontsize=20)
plt.xlabel('Number of Receivers',fontsize=20,loc='center')

#plt.xticks([100,200,300])
plt.semilogy()
plt.ylim((10**-4,10**6))
#plt.ylim([0,1000000])

plt.legend(loc='upper left',fontsize = "17")
plt.show()

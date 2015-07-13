from pylab import arange, plt
from drawnow import drawnow
import numpy as np
import time
from obspy.core import read

st = read('http://examples.obspy.org/COP.BHZ.DK.2009.050')
plt.ion() 
fig=plt.figure()
plt.ylim([-10000,10000])


def makeFig():
    time.sleep(.1);
    plt.plot(i, -9000, marker = ".");
    plt.plot(i, 9000, marker = ".");
    plt.xlim([x[0],x[0]+2000]);
    plt.plot(x,y, marker = '.') 

x=list()
y=list()
print len(x)
for i in arange(20000):
    temp_y=st[0].data[i];
    x.append(i)
    y.append(temp_y) # or any arbitrary update to your figure's data
    if(i > 2000):
    	if(i%200 == 0):
            drawnow(makeFig);
    	x.pop(0);
    	y.pop(0);
        
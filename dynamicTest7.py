from pylab import arange, plt
from drawnow import drawnow
import numpy as np
from obspy.core import read
import time

st = read('http://examples.obspy.org/COP.BHN.DK.2009.050')
plt.ion();
fig=plt.figure()
plt.ylim([-10000,10000])


def makeFig():
    time.sleep(.01);
    plt.plot(i, -9000);
    plt.plot(i, 9000);

    x = xrange(x_start, x_start+len(y));
    plt.xlim(x_start, x_start+len(y));
    plt.plot(x,y, color = 'black'); 

x_start = 0;
y=list()

for i in arange(20000):
    temp_y=st[0].data[i];
    y.append(temp_y);
    if(i > 2000):
        y.pop(0);
        x_start += 1;
    	if(i%200 == 0):
            drawnow(makeFig);

        
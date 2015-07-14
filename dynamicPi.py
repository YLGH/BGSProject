from pylab import arange, plt
from drawnow import drawnow
import numpy as np
import spidev

spi = spidev.SpiDev();
spi.open(0,0);

plt.ion();
fig=plt.figure()
plt.ylim([0,5000])


def makeFig():
    plt.plot(i, 0);
    plt.plot(i, 4096);
    plt.xlim(x_start, x_start+len(y));

    plt.plot(xrange(x_start, x_start+len(y)),y, color = 'black'); 

x_start = 0;
y=list()

i = 0;
while(True):
    byteArray= spi.xfer([0xff]*2);
    print byteArray;
    y.append((byteArray[0] << 8) + byteArray[1]);
    if(i > 2000):
        y.pop(0);
        x_start += 1;
    	if(i%200 == 0):
            drawnow(makeFig);
    i+=1;

spi.close();

        

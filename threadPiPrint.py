from collections import deque
#from obspy.core import read
from pylab import plt
from drawnow import drawnow
import threading
import time
#import cProfile
import spidev


def run():


	spi = spidev.SpiDev();
	spi.open(0,0);
	plt.ion();
	fig = plt.figure();
	q = deque(maxlen = 4000);
	c = deque();

	plt.ylim((0,4096));

	def getNext():
		global i;
		i = 0;
		while True:
			byteArray= spi.xfer([0xff]*2);
			print byteArray;
			q.append((byteArray[0] << 8) + byteArray[1]);
			i += 1;
			#time.sleep(.05);

	def makeFig():
		plt.plot(i, 4096);
		plt.plot(i, 0);
		plt.xlim(i, i + len(c));
		plt.plot(xrange(i, i+len(c)), c, color = 'black');

	def drawPlot():
		drawnow(makeFig);

	a = threading.Thread(target= getNext);
	a.start();


	while True:
		c = deque(q);
		print len(c);
		drawPlot();

#cProfile.run("run()");

run();

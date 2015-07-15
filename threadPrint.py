from collections import deque
from obspy.core import read
from pylab import plt
from drawnow import drawnow
import threading
import time
import cProfile


def run():

	st = read('http://examples.obspy.org/COP.BHN.DK.2009.050');
	plt.ion();
	fig = plt.figure();
	q = deque(maxlen = 200);
	c = deque();
	def getNext():
		global i;
		i = 0;
		while True:
			q.append(st[0].data[i]);
			i += 1;
			time.sleep(.005);

	def makeFig():
		plt.xlim(i, i + len(c));
		plt.plot(xrange(i, i+len(c)), c, color = 'black');

	def drawPlot():
		drawnow(makeFig);

	a = threading.Thread(target= getNext);
	a.daemon = True;
	a.start();


	while True:
		c = deque(q);
		print len(c);
		drawPlot();

cProfile.run("run()");
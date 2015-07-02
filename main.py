from mouse import moveTo
from generateData import generateData;	
from GaussNewtonMultiLat import getLocation
import time

for i in range(100):
	generateData();

	p = getLocation();
	x = p[0];
	y = p[1];
	moveTo(x,y);
	time.sleep(.5);

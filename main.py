from mouse import moveTo	
from GaussNewtonMultiLat import getLocation
import time

while True:
	#print getLocation();
	p = getLocation();
	x = p[0];
	y = p[1];
	moveTo(x,y);

	

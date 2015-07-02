from mouse import moveTo	
from GaussNewtonMultiLat import getLocation
import time

while True:
	p = getLocation();
	x = p[0];
	y = p[1];
	moveTo(x,y);
	

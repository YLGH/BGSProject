import random;
import math;


a = 1.68;
b = 1.05;
v = 4000;


def distance((x1,y1), (x2,y2)):
	return math.sqrt(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));

def generateData():
	randPoint = (random.uniform(.1,.9*a), random.uniform(.1,.9*b));


	d0 = distance(randPoint, (0,0));
	d1 = distance(randPoint, (a,0));
	d2 = distance(randPoint, (0,b));
	d3 = distance(randPoint, (a,b));

	t1Gen = (d1-d0)/v;
	t2Gen = (d2-d0)/v;
	t3Gen = (d3-d0)/v;

	return((t1Gen, t2Gen, t3Gen), randPoint);
g = generateData();
t1 = g[0][0];
t2 = g[0][1];
t3 = g[0][2];

print g


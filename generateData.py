import random;
import math;


f_settings = open('settings.in', 'r');
a = float(f_settings.readline());
b = float(f_settings.readline());
v = int(f_settings.readline());


def distance((x1,y1), (x2,y2)):
	return math.sqrt(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));

def generateData():
	randPoint = (random.uniform(.1,.9*a), random.uniform(.1,.9*b));

	d0 = distance(randPoint, (0,0));
	d1 = distance(randPoint, (a,0));
	d2 = distance(randPoint, (0,b));
	d3 = distance(randPoint, (a,b));

	t1 = (d1-d0)/v;
	t2 = (d2-d0)/v;
	t3 = (d3-d0)/v;

	g = ((t1, t2, t3), randPoint);

	f = open('timeDifference.in', 'wb');
	f.write(str(t1) + "\n");
	f.write(str(t2) + "\n");
	f.write(str(t3) + "\n");
	
	minVal = min(0, t1, t2, t3);
	print g[1]
	
	if(minVal == 0):
		f.write(str(0) + "\n");
	elif(minVal == t1):
		f.write(str(1) + "\n");
	elif(minVal == t2):
		f.write(str(2) + "\n");
	else:
		f.write(str(3) + "\n");
	
	f.write(str(g[1]));
	f.close();





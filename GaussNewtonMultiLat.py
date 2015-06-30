import math;
import numpy;
import random;

a = 1;
b = 1;
v = 4000;


def distance((x1,y1), (x2,y2)):
	return math.sqrt(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));

def generateData():
	randPoint = (random.uniform(0,a), random.uniform(0,b));

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

print(t1,t2,t3);
print(g[1]);

def dr1dx(x,y):
	return (x-a)/math.sqrt((x-a)*(x-a)+y*y) - x/math.sqrt(x*x+y*y);

def dr1dy(x,y):
	return y/math.sqrt((x-a)*(x-a)+y*y) - y/math.sqrt(x*x+y*y);

def dr2dx(x,y):
 	return x/math.sqrt(x*x+(y-b)*(y-b)) - x/math.sqrt(x*x+y*y);

def dr2dy(x,y):
 	return (y-b)/(x*x+(y-b)*(y-b)) - y/math.sqrt(x*x+y*y);

def dr3dx(x,y):
 	return (x-a)/math.sqrt((x-a)*(x-a)+(y-b)*(y-b)) - x/math.sqrt(x*x+y*y);

def dr3dy(x,y):
	return (y-b)/((x-a)*(x-a)+(y-b)*(y-b)) - y/math.sqrt(x*x+y*y);

def r(x,y):
	return ((math.sqrt((x-a)*(x-a)+y*y) - math.sqrt(x*x+y*y) - v*t1),
			(math.sqrt(x*x+(y-b)*(y-b)) - math.sqrt(x*x+y*y)-v*t2),
			(math.sqrt((x-a)*(x-a)+(y-b)*(y-b)) - math.sqrt(x*x+y*y)-v*t3));


def Gauss_NewtonSolve((x,y), first = False):
		#find first iteration
	#see Point

	#if first:
	#	guess = (.5,.5);
	#	while(distance(guess, (x,y)) > 1.75):
	#		guess = (random.uniform(0,a), random.uniform(0,b));
	#	return Gauss_NewtonSolve(guess);

	Jr = (( dr1dx(x,y),dr1dy(x,y)), (dr2dx(x,y), dr2dy(x,y)), (dr3dx(x,y), dr3dy(x,y)) );
	JrT = numpy.transpose(Jr);

	JrTJr = numpy.dot(JrT, Jr);

	JrTJr_i = numpy.linalg.inv(JrTJr);


	second_term = numpy.dot(numpy.dot(JrTJr_i, JrT), r(x,y));


	if(distance(second_term, (0,0)) < .00005):
		return (x,y);
	else:
		return Gauss_NewtonSolve(numpy.subtract((x,y), second_term));


print(Gauss_NewtonSolve((.5,.5), True));




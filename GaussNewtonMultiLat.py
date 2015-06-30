import math;
import numpy;
import random;



a = 1.68;
b = 1.05;
v = 4000;

screen_Width = 1680;
screen_Height = 1050;

#reading
f = open('timeDifference.in', 'r');
t1 = float(f.readline());
t2 = float(f.readline());
t3 = float(f.readline());

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

def distance((x1,y1), (x2,y2)):
	return math.sqrt(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));

def Gauss_NewtonSolve((x,y)):
	#try:
	Jr = (( dr1dx(x,y),dr1dy(x,y)), (dr2dx(x,y), dr2dy(x,y)), (dr3dx(x,y), dr3dy(x,y)) );
	JrT = numpy.transpose(Jr);
	JrTJr = numpy.dot(JrT, Jr);
	JrTJr_i = numpy.linalg.inv(JrTJr);

	second_term = numpy.dot(numpy.dot(JrTJr_i, JrT), r(x,y));

	#Does the iteration of B(s+1) =  B(s) - J^{+}J^{t}r*B(s))

	if(distance(second_term, (0,0)) < .00005):
		return (x,y);
	else:
		return Gauss_NewtonSolve(numpy.subtract((x,y), second_term));

	#except LinAlgError:
	#	return (x,y);



s = Gauss_NewtonSolve((.5,.5));
mouseLocation = (s[0]/a*screen_Width, s[1]/b*screen_Height);
print(s);
print(mouseLocation);



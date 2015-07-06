import math;
import numpy;
import serial;

f_settings = open('settings.in', 'r');
a = float(f_settings.readline());
b = float(f_settings.readline());
v = int(f_settings.readline());
screen_Width = int(f_settings.readline());
screen_Height = int(f_settings.readline());

ser = serial.Serial('/dev/ttyAMA0',115200,8);

def getLocation():
	read = map(int, ser.readline().split(" "));
	#return read;
	t1 = (read[1] - read[0])/48000000.0;
	t2 = (read[2] - read[0])/48000000.0;
	t3 = (read[3] - read[0])/48000000.0;
	
	print read;
	#return [t1*1E6 ,t2*1E6 ,t3*1E6];

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
		Jr = (( dr1dx(x,y),dr1dy(x,y)), (dr2dx(x,y), dr2dy(x,y)), (dr3dx(x,y), dr3dy(x,y)) );
		JrT = numpy.transpose(Jr);
		JrTJr = numpy.dot(JrT, Jr);
		JrTJr_i = numpy.linalg.inv(JrTJr);

		second_term = numpy.dot(numpy.dot(JrTJr_i, JrT), r(x,y));
		#Does the iteration of B(s+1) =  B(s) - J^{+}J^{t}r*B(s))
		if(distance(second_term, (0,0)) < .002):
			return (x,y);
		else:
			return Gauss_NewtonSolve(numpy.subtract((x,y), second_term));
	
	if(read[0] == 0):
		firstGuess = (.25*a, .25*b);
	elif(read[1] == 0):
		firstGuess = (.75*a, .25*b);
	elif(read[2] == 0):
		firstGuess = (.25*a, .75*b);
	else:
		firstGuess = (.75*a, .75*b);

	s = Gauss_NewtonSolve(firstGuess);
	mouseLocation = (round(s[0]/a*screen_Width), round(s[1]/b*screen_Height));
	return mouseLocation;



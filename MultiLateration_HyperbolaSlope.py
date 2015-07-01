import math;
import random;


x_d = 1;
y_d = 1;
speed = 4000;



def FindCoordinate(t1, t2, left_First):
	d1 = t1*speed;
	d2 = t2*speed;

	aux_1 = math.sqrt(x_d*x_d-d1*d1);
	aux_2 = math.sqrt(x_d*x_d-d2*d2);

	x_pos = (d1*d2*y_d)/(d2*aux_1+d1*aux_2);
	y_pos = -y_d/2 + aux_1/d1*x_pos;

	if(left_First):
		return (-x_pos, y_pos);
	else:
		return (x_pos, y_pos);

#print(FindCoordinate(.000000003,.0000000000002, True));
def distance((x1,y1), (x2,y2)):
	return math.sqrt(((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)));

def generateData():
	x_bound = x_d*.000000075;
	y_bound = y_d*.000000075;

	randPoint = (random.uniform(-x_bound/2, x_bound/2), random.uniform(-y_bound/2, y_bound/2));

	d_0 = distance(randPoint, (-.5, -.5));
	d_1 = distance(randPoint, (.5, -.5));
	d_2 = distance(randPoint, (-.5, .5));
	d_3 = distance(randPoint, (.5,.5));

	t_1 = math.fabs(d_1-d_0)/speed;
	t_2 = math.fabs(d_2-d_3)/speed;
	left_First = d_0 < d_1;
	print(randPoint);

	return(t_1, t_2, left_First)


g = generateData();
print(FindCoordinate(g[0], g[1], g[2]));


	







import math;

x_d = 100;
y_d = 100;
speed = 300;


#assert that t1,t2 < x_d/speed
#0.0471404521

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

print(FindCoordinate(.3,.2, True));




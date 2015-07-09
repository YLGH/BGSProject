from pymouse import PyMouse 

f_settings = open('settings.in', 'r');
a = float(f_settings.readline());
b = float(f_settings.readline());
v = int(f_settings.readline());
screen_Width = int(f_settings.readline());
screen_Height = int(f_settings.readline());

def moveTo(x,y):
	mouse = PyMouse();
	mouse.move(x,screen_Height-y);

def click(x,y):
	mouse = PyMouse();
	mouse.click(x, screen_Height-y); 
	#Has to flip since I defined 0,0 as the bottom left
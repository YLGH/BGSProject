from pymouse import PyMouse 

def moveTo(x,y):
	mouse = PyMouse();
	#mouse.move(x,y);
	mouse.click(x,y);

	#d = display.Display();
	#s = d.screen();
	#root = s.root;
	#root = root.warp_pointer(x,y);
	#d.sync()
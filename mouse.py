from Xlib import X, display
import time

def moveTo(x,y):
	d = display.Display();
	s = d.screen();
	root = s.root;
	root = root.warp_pointer(x,y);
	d.sync()
from Xlib import X, display
d = display.Display();
s = d.screen();
root = s.root;
root.wrap_pointer(300,300);
d.sync();
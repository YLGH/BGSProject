from Xlib import X, display
import time

d = display.Display()
s = d.screen()
root = s.root
root.warp_pointer(500,500)
d.sync()

time.sleep( 5 )
root.warp_pointer(250,250)
d.sync()

time.sleep( 5 )
root.warp_pointer(100,100)
d.sync()

time.sleep( 5 )
root.warp_pointer(250,250)
d.sync()
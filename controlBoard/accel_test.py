import boardControlLib as b
import math
import time
import threading
from rotating_cube import Simulation
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port name>"
	sys.exit(1)

test = b.BoardControlLib(sys.argv[1])

sim = Simulation()

def runsim():
	sim.run()

def datatask():
	tstart = time.time()
	tot = [0,0,0]
	cnt = 0
	while (time.time() - tstart) < 1:
		vals = test.get_accel_values()
		tot[0] += vals[0]
		tot[1] += vals[1]
		tot[2] += vals[2]
		cnt += 1
	calib = [tot[0]/float(cnt), tot[0]/float(cnt), tot[0]/float(cnt)]

	while True:
		tstart = time.time()
		tot = [0,0,0]
		cnt = 0
		while (time.time() - tstart) < 0.05:
			vals = test.get_accel_values()
			tot[0] += vals[0]
			tot[1] += vals[1]
			tot[2] += vals[2]
			cnt += 1
		accel = [tot[0]/float(cnt), tot[1]/float(cnt), tot[2]/float(cnt)]
		dx = accel[0] - calib[0]
		dy = accel[1] - calib[1]
		dz = accel[2] - calib[2]
		
		y2 = dy * dy
		z2 = dz * dz
		
		roll = math.atan2(dy, dz)
		pitch = math.atan2(-dx, math.sqrt(y2 + z2))
		
		print math.degrees(pitch), math.degrees(roll)
		
		sim.pitch = math.degrees(pitch)
		sim.roll = math.degrees(roll)
		
datathread = threading.Thread(target=datatask)
datathread.daemon = True
datathread.start()

runsim()
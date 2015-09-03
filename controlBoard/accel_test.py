import accel_convert
from rotating_cube import Simulation
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port name>"
	sys.exit(1)

accel = accel_convert.Accel(sys.argv[1])
sim = Simulation()

def runsim():
	sim.run()

def ac_cb(pitch, roll):
	sim.pitch = pitch
	sim.roll = roll
	print(pitch, roll)

accel.start(ac_cb)
runsim()
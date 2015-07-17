import SensDisLib as s
import time as t
from collections import deque

sensor = s.SensorDisplay()

#We want to see a total of 17 peaks, for 16 time differences


buff16 = deque(maxlen = 16)
currentSum = 0.0

def addValue(i):
	global currentSum
	if(len(buff16) == 16):
		currentSum -= buff16[0]

	buff16.append(i)
	currentSum += i;
	return currentSum/len(buff16)


	
sensor.add_sensor_one("Heartbeat")
sensor.setVoltageFunction_sensor(1, addValue)

sensor.runPlot()
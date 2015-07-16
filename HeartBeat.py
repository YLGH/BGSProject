import SensDisLib as s
import time as t

sensor = s.SensorDisplay()

#We want to see a total of 17 peaks, for 16 time differences

numPeaks = 0
threshHold = 1900

peakTimes = list()

lastVoltage = 0
thisVoltage = 0
while numPeaks < 17:
	thisVoltage = sensor.get_Raw_Sensor(1)
	if(thisVoltage >= threshHold and lastVoltage < threshHold):
		peakTimes.append(t.time())
		numPeaks += 1
	lastVoltage = thisVoltage


print peakTimes





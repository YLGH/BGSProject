import Displays/SensDisLib as s
import time as t

sensor = s.SensorDisplay()

#We want to see a total of 17 peaks, for 16 time differences

numPeaks = 0
threshHold = 2025

peakTimes = list()

lastVoltage = 0
thisVoltage = 0
while numPeaks < 17:
	lastVoltage = thisVoltage
	thisVoltage = 0
	#average over 16 measurements
	for i in xrange(64):
		thisVoltage += sensor.get_Raw_Sensor(1)
	thisVoltage /= 64
	if(thisVoltage >= threshHold and lastVoltage < threshHold):
		peakTimes.append(t.time())
		numPeaks += 1
	lastVoltage = thisVoltage

timeDifference = []

for i in range(1, 16):
	timeDifference.append(peakTimes[i]-peakTimes[i-1])

print peakTimes
print timeDifference






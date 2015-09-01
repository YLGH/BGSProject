import SensDisLib as s
import time
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port name>"
	sys.exit(1)

def double(x):
	return 2*x;

def voltToTemp(x):
	return (((x*3.3)/4096.0) - 0.4)/0.01953

def to16bit(x):
	return x >> 8
	
test = s.SensorDisplay(sys.argv[1])
test.add_sensor_one("S1")
test.add_sensor_two("S2")
test.add_sensor_three("S3")
test.add_sensor_four("S4")

#test.setYRange_sensor_one(0, 65536)
#test.setYRange_sensor_two(0, 65536)
#test.setYRange_sensor_three(0, 65536)
#test.setYRange_sensor_four(0, 65536)

test.setYRange_sensor_one(-32768, 32768)
test.setYRange_sensor_two(-32768, 32768)
test.setYRange_sensor_three(-32768, 32768)
test.setYRange_sensor_four(-32768, 32768)

test.setVoltageFunction_sensor(1, to16bit)
test.setVoltageFunction_sensor(2, to16bit)
test.setVoltageFunction_sensor(3, to16bit)
test.setVoltageFunction_sensor(4, to16bit)

#test.setYRange_Sensor_Three(1900, 2000)
#test.setYRange_Sensor_Three(20, 40)
#test.setVoltageFunction_Sensor_One(double);
#test.setVoltageFunction_Sensor_Three(voltToTemp)

test.runPlot()
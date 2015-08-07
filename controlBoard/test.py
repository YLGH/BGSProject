import SensDisLib as s
import time
def double(x):
	return 2*x;

def voltToTemp(x):
	return (((x*3.3)/4096.0) - 0.4)/0.01953

def to16bit(x):
	return x >> 8
	
test = s.SensorDisplay()
test.add_sensor_one("Test")
test.add_sensor_two("S2")
test.add_sensor_three("TWANGER")
test.add_sensor_four("Temperature")

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
#while True:
#	time.sleep(.01)
#	print test.get_Raw_Sensor(1)
#	print test.get_Raw_Sensor(2)
#	print test.get_Raw_Sensor(3)
#	print test.get_Raw_Sensor(4)
#	print " "


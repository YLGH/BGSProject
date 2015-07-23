import SensDisLib as s
import time
def double(x):
	return 2*x;

def voltToTemp(x):
	return (((x*3.3)/4096.0) - 0.4)/0.01953; 

test = s.SensorDisplay()
test.add_sensor_three("Piezo Disk")
test.add_sensor_four("Geophone One")
#test.setYRange_sensor_one(1900, 2500)
#test.add_Sensor_One("Test");
#test.add_Sensor_Two("Microphones")
#test.add_Sensor_Three("TWANGER")
#test.setYRange_Sensor_Three(1900, 2000)
#test.add_Sensor_Four("Temperature")
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


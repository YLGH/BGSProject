import SensDisLib as s

def double(x):
	return 2*x;

def voltToTemp(x):
	return (((x*3.3)/4096.0) - 0.4)/0.01953; 

test = s.SensorDisplay()
test.add_Sensor_One("Geophone One")
#test.add_Sensor_One("Test");
test.add_Sensor_Two("Geophone Two")
test.add_Sensor_Three("TWANGER")
test.add_Sensor_Four("Temperature")
#test.setYRange_Sensor_Three(20, 40)
#test.setVoltageFunction_Sensor_One(double);
#test.setVoltageFunction_Sensor_Three(voltToTemp)


test.run()


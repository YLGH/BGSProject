import boardControlLib as b
import time
import datetime
import calendar
import sys

if len(sys.argv)<2:
	print "Usage: " + sys.argv[0] + " <port_name>"
	sys.exit(1)

test = b.BoardControlLib(sys.argv[1])

print "Board version:", test.get_firmware_string()

print "Sensor 1 name:", test.get_sensor_name(1)
print "Sensor 2 name:", test.get_sensor_name(2)
print "Sensor 3 name:", test.get_sensor_name(3)
print "Sensor 4 name:", test.get_sensor_name(4)

print "Sample rate:", test.get_sample_rate()

print "File type:", test.get_file_format()

for i in range(1,8):
	test.enable_sensor(i)

print "Sensor 1 enabled:", test.is_sensor_enabled(1)
print "Sensor 2 enabled:", test.is_sensor_enabled(2)
print "Sensor 3 enabled:", test.is_sensor_enabled(3)
print "Sensor 4 enabled:", test.is_sensor_enabled(4)

print "Accelerometer X enabled:", test.is_sensor_enabled(5)
print "Accelerometer Y enabled:", test.is_sensor_enabled(6)
print "Accelerometer Z enabled:", test.is_sensor_enabled(7)

print "Channel gains:"
print "Sensor 1: ", str(test.get_gain(1)) + "x"
print "Sensor 2: ", str(test.get_gain(2)) + "x"
print "Sensor 3: ", str(test.get_gain(3)) + "x"
print "Sensor 4: ", str(test.get_gain(4)) + "x"

print "Current sensor values:"
vals = test.get_sensor_values()
print "Sensor 1: ", vals[0]
print "Sensor 2: ", vals[1]
print "Sensor 3: ", vals[2]
print "Sensor 4: ", vals[3]

print "Scheduling enabled:", test.is_scheduling_enabled()

tm = datetime.datetime.utcfromtimestamp(test.get_scheduled_start())
print "Scheduling start:", tm.strftime("%Y-%m-%d %H:%M:%S")
tm = datetime.datetime.utcfromtimestamp(test.get_scheduled_end())
print "Scheduling end:", tm.strftime("%Y-%m-%d %H:%M:%S")

tm = datetime.datetime.utcfromtimestamp(test.get_rtc_time())
print "RTC time:", tm.strftime("%Y-%m-%d %H:%M:%S")

#test.reset_processor()

#print "Setting scheduling..."
#test.set_scheduled_start(calendar.timegm((2015, 7, 26, 10, 1, 0)))
#test.set_scheduled_end(calendar.timegm((2015, 7, 26, 10, 1, 30)))
#test.enable_scheduling()

#print "Connecting to card..."
#if test.initialize_card():
#	print "Card ready"
#	
#	print "Switching to CSV Format..."
#	
#	print "Logging .csv for 2 second at 5SPS..."
#	test.set_CSV()
#	test.set_Binary()
#	test.set_sample_rate(5)
#	test.start_logging()
#	time.sleep(2)
#	test.stop_logging()
#	print "Done!"
#	
#	print "Logging .bin for 4 seconds at 1000SPS..."
#	test.set_Binary()
#	test.set_sample_rate(1000)
#	test.start_logging()
#	time.sleep(4)
#	test.stop_logging()
#	print "Done!"
#else:
#	print "Card init failed!"
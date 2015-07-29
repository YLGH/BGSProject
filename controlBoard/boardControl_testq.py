import boardControlLib as b
import time
import datetime
import calendar

test = b.BoardControlLib('COM6')

print "Board version:", test.get_firmware_string()

print "Sensor 1 name:", test.get_sensor_name(1)
print "Sensor 2 name:", test.get_sensor_name(2)
print "Sensor 3 name:", test.get_sensor_name(3)
print "Sensor 4 name:", test.get_sensor_name(4)

print "Sample rate:", test.get_sample_rsate()

print "File type:", test.get_file_format()

print "Sensor 1 enabled:", test.is_sensor_enabled(1)
print "Sensor 2 enabled:", test.is_sensor_enabled(2)
print "Sensor 3 enabled:", test.is_sensor_enabled(3)
print "Sensor 4 enabled:", test.is_sensor_enabled(4)

#test.enable_scheduling()

print "Scheduling enabled:", test.is_scheduling_enabled()

tm = datetime.datetime.utcfromtimestamp(test.get_scheduled_start())
print "Scheduling start:", tm.strftime("%Y-%m-%d %H:%M:%S")
tm = datetime.datetime.utcfromtimestamp(test.get_scheduled_end())
print "Scheduling end:", tm.strftime("%Y-%m-%d %H:%M:%S")

tm = datetime.datetime.utcfromtimestamp(test.get_rtc_time())
print "RTC time:", tm.strftime("%Y-%m-%d %H:%M:%S")

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

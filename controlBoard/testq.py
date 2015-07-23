import boardControlLib as b
import time

test = b.BoardControlLib()

print "Board version:", test.get_firmware_string()

#print "Setting names..."
#test.set_sensor_name(1, "Hello")
#test.set_sensor_name(2, "this")
#test.set_sensor_name(3, "is")
#test.set_sensor_name(4, "test")

#print "Enabling sensor 1 only."
#test.enable_sensor(1)
#test.disable_sensor(2)
#test.disable_sensor(3)
#test.disable_sensor(4)

print

print "Sensor 1 name:", test.get_sensor_name(1)
print "Sensor 2 name:", test.get_sensor_name(2)
print "Sensor 3 name:", test.get_sensor_name(3)
print "Sensor 4 name:", test.get_sensor_name(4)

print "Sample rate:", test.get_sample_rate()

print "File type:", test.get_file_format()

print "Sensor 1 enabled:", test.is_sensor_enabled(1)
print "Sensor 2 enabled:", test.is_sensor_enabled(2)
print "Sensor 3 enabled:", test.is_sensor_enabled(3)
print "Sensor 4 enabled:", test.is_sensor_enabled(4)

print "Connecting to card..."
if test.initialize_card():
	print "Card ready"
	
	#print "Switching to CSV Format..."
	
#	print "Logging .csv for 2 second at 5SPS..."
#	test.set_CSV()
#	test.set_Binary()
#	test.set_sample_rate(5)
#	test.start_logging()
#	time.sleep(2)
#	test.stop_logging()
#	print "Done!"
	
#	print "Logging .bin for 4 seconds at 1000SPS..."
#	test.set_Binary()
#	test.set_sample_rate(1000)
#	test.start_logging()
#	time.sleep(4)
#	test.stop_logging()
#	print "Done!"
else:
	print "Card init failed!"

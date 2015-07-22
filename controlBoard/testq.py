import boardControlLib as b
import time

test = b.BoardControlLib()

print "Board version:", test.get_firmware_string()

#print "Setting names..."
#test.set_name_sensor(1, "Test 1")
#test.set_name_sensor(2, "Test 2")
#test.set_name_sensor(3, "Test 3")
#test.set_name_sensor(4, "Test 4")

print

print "Sensor 1 name:", test.get_name_sensor(1)
print "Sensor 2 name:", test.get_name_sensor(2)
print "Sensor 3 name:", test.get_name_sensor(3)
print "Sensor 4 name:", test.get_name_sensor(4)

print

print "Sample rate:", test.get_sample_rate()

print

print "File type:", test.get_file_format()

#print "Setting sensor names..."
#test.set_name_sensor(1, "Jamie's Heartbeat");
#test.set_name_sensor(2, "The second sensor");
#test.set_name_sensor(3, "The TWANGER");
#test.set_name_sensor(4, "Temperature");

#print "Connecting to card..."
#if test.initialize_card():
#	print "Card ready"
	
#	print "Switching to CSV Format..."
	
	#print "Logging .csv for 10 second at 0.5SPS..."
	#test.set_CSV()
	#test.set_sample_rate(.5)
	#test.start_logging()
	#time.sleep(10)
	#test.stop_logging()
	#print "Done!"
	
	
#	print "Logging .bin for 4 seconds at 1000SPS..."
#	test.set_Binary()
#	test.set_sample_rate(1000)
#	test.start_logging()
#	time.sleep(4)
#	test.stop_logging()
#	print "Done!"
#else:
#	print "Card init failed!"

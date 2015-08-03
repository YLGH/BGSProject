import Filetype as f
import Sensor as s
import time
from math import floor

class UARTComm:
	def __init__(self, cport):
		import serial
		self.ser = serial.Serial(cport, 115200, timeout=2)
	
	def send(self, vals):
		self.ser.write(vals)
	
	def recv(self, count):
		val = bytearray(self.ser.read(count))
		return val

class SPIComm:
	def __init__(self):
		import spidev
		self.spi = spidev.SpiDev()
		self.spi.open(0,0)
	
	def send(self, vals):
		self.spi.xfer(vals)
	
	def recv(self, count):
		return self.spi.xfer([0xff]*count)

class BoardControlLib:

	def __init__(self, cport=None):

		self.cardInitialized = False
		self.recording = False

		self.sensors = [s.Sensor(), s.Sensor(), s.Sensor(), s.Sensor()]
		self.fileType = f.Filetype()

		if cport is None:
			self.comm = SPIComm()
		else:
			self.comm = UARTComm(cport)

	def send(self, vals):
		self.comm.send(vals)
	
	def recv(self, count):
		return self.comm.recv(count)
		
	def get_sensor_values(self):
		self.send([0x01])
		out = []
		for i in range(4):
			val = self.recv(2)
			out.append((val[0] << 8) | val[1])
		return out
		
	def set_sensor_name(self, index, name_String):
		assert(not self.recording), "Can't change while recording!"
		self.send([0x02])
		self.send([len(name_String) + 1])
		self.send([index-1])
		for letter in name_String:
			self.send([ord(letter)])
	
	def set_sample_rate(self, sampleRate):
		assert(not self.recording), "Can't change while recording!"
		self.send([0x03])
		self.send([4])
		sd = int(100000/sampleRate)
		self.send([(sd >> 24) & 0xFF, (sd>>16) & 0xFF, (sd >> 8) & 0xFF, sd & 0xFF])

	def start_logging(self):
		assert(self.cardInitialized), "CARD IS NOT INITIALIZED"
		self.send([0x04])
		self.recording = True

	def stop_logging(self):
		assert(self.recording), "CARD IS NOT RECORDING"
		self.send([0x05])
		self.recording = False

	def initialize_card(self):
		assert(not self.recording), "Can't initialize while recording!"
		self.send([0x06])
		reps = 0
		while reps<20:
			if self.is_card_ready():
				self.cardInitialized = True
				return True
			reps += 1
			time.sleep(0.1)
		self.cardInitialized = False
		return False

	def is_card_ready(self):
		self.send([0x07])
		return (self.recv(1)[0] == 1)

	def set_Raw(self):
		assert(not self.recording), "Can't change while recording!"
		fileType = f.Binary(self.comm)
		fileType.indicate()
		
	def set_CSV(self):
		assert(not self.recording), "Can't change while recording!"
		fileType = f.CSV(self.comm)
		fileType.indicate()
		
	def get_firmware_string(self):
		self.send([0x11])
		namelen = self.recv(1)[0]
		assert(namelen<32), "NAME TOO LONG?!?"
		return ''.join(map(chr, self.recv(namelen)))
		
	def get_sensor_name(self, index):
		self.send([0x12])
		self.send([0x01])
		self.send([index-1])
		namelen = self.recv(1)[0]
		assert(namelen<32), "NAME TOO LONG?!?"
		return ''.join(map(chr, self.recv(namelen)))

	def get_sample_rate(self):
		self.send([0x13])
		val = self.recv(4)
		sr = 100000.0/((val[0]<<24) + (val[1]<<16) + (val[2]<<8) + val[3])
		return sr
		
	def get_file_format(self):
		self.send([0x14])
		val = self.recv(1)[0]
		if val == 1: return "Raw"
		elif val == 2: return "CSV"
		else: return "ERROR"
	
	def enable_sensor(self, index):
		assert(not self.recording), "Can't change while recording!"
		self.send([0x15])
		self.send([0x01])
		self.send([index-1])

	def disable_sensor(self, index):
		assert(not self.recording), "Can't change while recording!"
		self.send([0x16])
		self.send([0x01])
		self.send([index-1])

	def is_sensor_enabled(self, index):
		self.send([0x17])
		val = self.recv(1)[0]
		return (val & (1 << (index-1))) > 0

	def set_scheduled_start(self, timestamp):
		self.send([0x18])
		self.send([4])
		self.send([(timestamp >> 24) & 0xFF, (timestamp>>16) & 0xFF, (timestamp >> 8) & 0xFF, timestamp & 0xFF])
	
	def set_scheduled_end(self, timestamp):
		self.send([0x19])
		self.send([4])
		self.send([(timestamp >> 24) & 0xFF, (timestamp>>16) & 0xFF, (timestamp >> 8) & 0xFF, timestamp & 0xFF])
	
	def enable_scheduling(self):
		self.send([0x20])
		
	def disable_scheduling(self):
		self.send([0x21])
	
	def set_rtc_time(self, timestamp):
		self.send([0x22])
		self.send([4])
		self.send([(timestamp >> 24) & 0xFF, (timestamp>>16) & 0xFF, (timestamp >> 8) & 0xFF, timestamp & 0xFF])

	def get_rtc_time(self):
		self.send([0x23])
		val = self.recv(4)
		ts = (val[0]<<24) + (val[1]<<16) + (val[2]<<8) + val[3]
		return ts
	
	def save_settings(self):
		self.send([0x24])
		time.sleep(0.2)
	
	def is_scheduling_enabled(self):
		self.send([0x25])
		return self.recv(1)[0] == 1

	def get_scheduled_start(self):
		self.send([0x26])
		val = self.recv(4)
		return (val[0]<<24) + (val[1]<<16) + (val[2]<<8) + val[3]

	def get_scheduled_end(self):
		self.send([0x27])
		val = self.recv(4)
		return (val[0]<<24) + (val[1]<<16) + (val[2]<<8) + val[3]
		


'''
0x01: We want to retrieve the information on the four sensors
0x02: We want to set the name - followed by which sensor - followed by a String (length, then characters)
0x03: Set sample delay - followed by a 4-byte integer (x10us)
0x04: start logging
0x05: stop logging
0x06: initialize the card
0x07: is card ready?
0x08: Raw Filetype
0x09: CSV FileType
0x0A-F: reserved for file type
0x11: report firmware version String
0x12: Get sensor name - followed by which sensor
0x13: Get sample delay
0x14: get filetype: 1 for Raw, 2 for CSV
0x15: Enable sensor - followed by which sensor
0x16: Disable sensor - followed by which sensor
0x17: Get enabled sensors mask
0x18: Set scheduled start time - followed by 4-byte unix timestamp
0x19: Set scheduled end time - followed by 4-byte unix timestamp
0x20: Enable scheduling
0x21: Disable scheduling
0x22: Set RTC time - followed by 4-byte unix timestamp
0x23: Get RTC time
0x24: Save settings to EEPROM
0x25: Is scheduling enabled?
0x26: Get scheduled start time
0x27: Get scheduled end time
'''



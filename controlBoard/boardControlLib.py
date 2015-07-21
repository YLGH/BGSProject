import spidev
import Filetype as f
import Sensor as s
import time
from math import floor


#Configure which channels to log

#What to name each channel

#Sample rate

#What is the file output type

#initialize card

#start/pause/stop recording

#start/stop for this amount of time

class BoardControlLib:

	def __init__(self):

		self.cardInitialized = False
		self.recording = False

		self.sensors = [s.Sensor(), s.Sensor(), s.Sensor(), s.Sensor()]
		self.fileType = f.Filetype()

		self.spi = spidev.SpiDev()
		self.spi.open(0,0)

	def set_CSV(self):
		fileType = f.CSV(self.spi)
		fileType.indicate()

	def set_Binary(self):
		fileType = f.Binary(self.spi)
		fileType.indicate()

	def set_sample_rate(self, sampleRate):
		self.spi.xfer([0x03])
		self.spi.xfer([2])
		sd = int(1000/sampleRate)
		self.spi.xfer([(sd >> 8) & 0xFF, sd & 0xFF])

	def start_logging(self):
		assert(self.cardInitialized), "CARD IS NOT INITIALIZED"
		self.spi.xfer([0x04])
		self.recording = True

	def stop_logging(self):
		assert(self.recording), "CARD IS NOT RECORDING"
		self.spi.xfer([0x05])
		self.recording = False

	def initialize_card(self):
		self.spi.xfer([0x06])
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
		self.spi.xfer([0x07])
		return (self.spi.xfer([0xff])[0] == 1)

	def set_name_sensor(self, index, name_String):
		self.spi.xfer([0x02])
		self.spi.xfer([len(name_String) + 1])
		self.spi.xfer([index-1])
		for letter in name_String:
			self.spi.xfer([ord(letter)])

	def get_firmware_string(self):
		self.spi.xfer([0x11])
		namelen = self.spi.xfer([0xff])[0]
		assert(namelen<32), "NAME TOO LONG?!?"
		return ''.join(map(chr, self.spi.xfer([0xff]*namelen)))






'''0x01: We want to retrieve the information on the four sensors
0x02: We want to set the name - followed by which sensor - followed by a String (length, then characters)
0x03: Set sample rate - followed by an integer
0x04: start logging
0x05: stop logging
0x06: initialize the card
0x07: is card ready?
0x08: Binary Filetype
0x09: CSV FileType
0x0A-F: reserved for file type
0x11: report firmware version String


[0xffff]: Dummy data that we have to send by convention'''



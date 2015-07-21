import spidev
import Filetype


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

		self.sensors = [Sensor(), Sensor(), Sensor(), Sensor()]
		self.fileType = FileType()

		self.spi = spidev.SpiDev()
		self.spi.open(0,0)

	def set_CSV(self):
		fileType = CSV()
		fileType.indicate()

	def set_Binary(self):
		fileType = binary()
		fileType.indicate()

	def set_sample_rate(self, index, sampleRate):
		spi.xfer([0x03])
		spi.xfer([samplerate])

	def start_logging(self, index):
		assert(self.cardInitialized), "CARD IS NOT INITIALIZED"
		spi.xfer([0x04])
		self.recording = True

	def stop_logging(self, index):
		assert(self.recording), "CARD IS NOT RECORDING"
		spi.xfer([0x05])
		self.recording = False

	def initialize_card(self):
		spi.xfer([0x06])
		self.cardInitialized = True

	def set_name_sensor(self, index, name_String):
		spi.xfer([0x02])
		spi.xfer([index])
		spi.xfer([len(name)])
		for letter in name_String:
			spi.xfer([ord(letter)])

	def get_firmware_string(self):
		spi.xfer([0x11])
		return spi.xfer([0xff]*2)






'''0x01: We want to retrieve the information on the four sensors
0x02: We want to set the name - followed by which sensor - followed by a String (length, then characters)
0x03: Set sample rate - followed by an integer
0x04: start logging
0x05: stop logging
0x06: initialize the card
0x07: Binary Filetype
0x08: CSV FileType
0x09: reserved for file type
0x0A-F: reserved for file type
0x11: report firmware version String


[0xffff]: Dummy data that we have to send by convention'''



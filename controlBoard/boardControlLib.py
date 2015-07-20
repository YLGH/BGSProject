import spidev
import Filetype


#Configure which channels to log

#What to name each channel

#Sample rate per channel

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

	def start_log(self):
		#spidev to send
		pass

	def set_CSV(self):
		fileType = CSV()
		fileType.indicate()

	def set_Binary(self):
		fileType = binary()
		fileType.indicate()

	def set_sample_rate(self, index, sampleRate):
		channel[index-1].set_sample_rate

	def start_logging(self, index):
		#loop through and xfer
		pass

	def stop_logging(self, index):
		#loop through and xfer
		pass

	def initialize_card(self):
		#have it talk to the card, before we do any operations
		pass

	def start_record(self):
		#indicate we need to record
		pass

	def stop_record(self):
		#indicate we want to stop recording
		pass






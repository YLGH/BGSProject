import spidev

class Sensor:

	def __init__(self):
		#Default Settings

		self.name = "Sensor"
		self.toLog = False
		self.sampleRate = 100

		self.displayFunction = lambda x: x

	def set_name(self, newName):
		assert(isinstance(newName, str)), "The name must be a String!"
		self.name = newName

	def set_sample_rate(self, sampleRate):
		assert(isinstance(sampleRate, int) and sampleRate <= 1000 and sampleRate >= 1), "The sample rate must be an integer between 1 and 1000!"
		self.sampleRate = sampleRate;
		#spi.xfer over the sampleRate


	def start_logging(self):
		self.toLog = True

	def stop_logging(self):
		self.toLog = False


	def get_raw(self):
		byteArray = self.spi.xfer([0x01])
		byteArray = self.spi.xfer([0xff]*8)
		return (byteArray[2*index] << 8) + byteArray[2*index+1]

	def setVoltageFunction(self, newFunc):
		self.displayFunction = lambda x: newFunc(x)

	def get_cook(self):
		return self.displayFunction(get_raw())
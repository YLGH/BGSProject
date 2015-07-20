import spidev



#Configure which channels to log

#What to name each channel

#Sample rate per channel

#What is the file output type

#initialize card

#start/pause/stop recording

#start/stop for this amount of time

class BoardControlLib:

	def __init__(self):

		self.sensors = [Sensor(), Sensor(), Sensor(), Sensor()]
		return
		self.spi = spidev.SpiDev()
		self.spi.open(0,0)



class FileType:

	def __init__(self):
		self.type = "NOT_SET"

	def sendData():
		pass


class CSV(FileType):
	def __init__(self):
		self.typeName = "CSV"

	def sendData():
		return
		#Implement SendData type


class Binary(FileType):
	def __init__(self):
		self.typeName = "CSV"

	def sendData():
		return
		#Implement SendData type


class Sensor:

	def __init__(self):
		#Default Settings

		self.name = "Sensor"
		self.toLog = False
		self.sampleRate = 100


	def set_name(self, newName):
		assert(isinstance(newName, str)), "The name must be a String!"
		self.name = newName

	def set_sample_Rate(self, sampleRate):
		assert(isinstance(sampleRate, int) and sampleRate <= 1000 and sampleRate >= 1), "The sample rate must be an integer between 1 and 1000!"
		self.sampleRate = sampleRate;

	def start_logging():
		self.toLog = True

	def stop_logging():
		self.toLog = False



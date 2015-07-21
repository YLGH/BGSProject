class Filetype:

	def __init__(self):
		self.type = "NOT_SET"

	def indicate(self):
		assert(False), "File type not set!"

	def getTypeString(self):
		return self.typeName




class Binary(Filetype):
	def __init__(self, spi):
		self.typeName = "Binary"
		self.spi = spi

	def indicate(self):
		self.spi.xfer([0x08])


class CSV(Filetype):
	def __init__(self, spi):
		self.typeName = "CSV"
		self.spi = spi

	def indicate(self):
		self.spi.xfer([0x09])
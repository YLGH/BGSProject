class Filetype:

	def __init__(self):
		self.type = "NOT_SET"

	def indicate(self):
		assert(False), "File type not set!"

	def getTypeString(self):
		return self.typeName




class Binary(Filetype):
	def __init__(self):
		self.typeName = "Binary"

	def indicate(self):
		spi.xfer([0x07])


class CSV(Filetype):
	def __init__(self):
		self.typeName = "CSV"

	def indicate(self):
		spi.xfer([0x08])
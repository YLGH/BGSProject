class Filetype:

	def __init__(self):
		self.type = "NOT_SET"

	def indicate(self):
		assert(False), "File type not set!"

	def getTypeString(self):
		return self.typeName


class CSV(Filetype):
	def __init__(self):
		self.typeName = "CSV"

	def indicate(self):
		print "CSV"
		#return
		#Implement SendData type


class Binary(Filetype):
	def __init__(self):
		self.typeName = "Binary"

	def indicate(self):
		return
		#Implement SendData type

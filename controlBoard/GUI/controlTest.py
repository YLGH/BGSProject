import sys
from PyQt4 import QtCore, QtGui, uic

form_class = uic.loadUiType("controlTest.ui")[0]

class MyWindowClass(QtGui.QMainWindow, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.initialize_button.clicked.connect(self.initialize_handle)
		self.start_logging.clicked.connect(self.start_logging_handle)
		self.stop_logging.clicked.connect(self.stop_logging_handle)

	def initialize_handle(self):
		print "Initializing"

	def start_logging_handle(self):
		print "Sample rate at " + str(self.sample_Rate.value())
		print "Start logging"

	def stop_logging_handle(self):
		print "Stopped Logging"





app = QtGui.QApplication(sys.argv)
myWindow = MyWindowClass(None)
myWindow.show()
app.exec_()
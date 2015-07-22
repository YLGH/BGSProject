import sys
from PyQt4 import QtCore, QtGui, uic
import boardControlLib as b

board = b.BoardControlLib()

form_class = uic.loadUiType("controlTest.ui")[0]

class MyWindowClass(QtGui.QMainWindow, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.initialize_button.clicked.connect(self.initialize_handle)
		self.start_logging.clicked.connect(self.start_logging_handle)
		self.stop_logging.clicked.connect(self.stop_logging_handle)

	def initialize_handle(self):
		board.initialize_card()
		print(self.sample_Rate.value())
		board.set_sample_rate(self.sample_Rate.value())
		print "Initializing"

	def start_logging_handle(self):
		board.start_logging()
		print "Start logging"

	def stop_logging_handle(self):
		board.stop_logging()
		print "Stopped Logging"





app = QtGui.QApplication(sys.argv)
myWindow = MyWindowClass(None)
myWindow.show()
app.exec_()

import sys
from PyQt4 import QtCore, QtGui, uic
import boardControlLib as b

board = b.BoardControlLib()

form_class = uic.loadUiType("controlTest.ui")[0]

class MyWidget(QtGui.QWidget, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.initialize_card_button.clicked.connect(self.initialize_handle)
		self.start_logging_button.clicked.connect(self.start_logging_handle)
		self.stop_logging_button.clicked.connect(self.stop_logging_handle)

		self.sensor_one_setName.clicked.connect(self.sensor_one_setName_handle)
		self.sensor_one_enable.toggled.connect(self.sensor_one_enable_handle)

	def initialize_handle(self):
		board.initialize_card()
		print "Initializing"

	def start_logging_handle(self):
		board.set_sample_rate(self.sample_Rate.value())
		board.start_logging()
		print "Start logging"

	def stop_logging_handle(self):
		board.stop_logging()
		print "Stopped Logging"

	def sensor_one_setName_handle(self):
		board.set_name_sensor(1, self.sensor_one_name.text())

	def sensor_one_enable_handle(self):
		print self.sensor_one_enable.isChecked()


app = QtGui.QApplication(sys.argv)
myWidget = MyWidget(None)
myWidget.show()
app.exec_()


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

		self.sensor_two_setName.clicked.connect(self.sensor_two_setName_handle)
		self.sensor_two_enable.toggled.connect(self.sensor_two_enable_handle)

		self.sensor_three_setName.clicked.connect(self.sensor_three_setName_handle)
		self.sensor_three_enable.toggled.connect(self.sensor_three_enable_handle)

		self.sensor_four_setName.clicked.connect(self.sensor_four_setName_handle)
		self.sensor_four_enable.toggled.connect(self.sensor_four_enable_handle)

	def initialize_handle(self):
		print "Initializing"
		board.initialize_card()

	def start_logging_handle(self):
		setFile = {0: board.set_CSV, 1: board.set_Binary}
		setFile[self.filetype.currentIndex()]()
		board.set_sample_rate(self.sample_rate.value())
		board.start_logging()
		print "Start logging"

	def stop_logging_handle(self):
		board.stop_logging()
		print "Stopped Logging"

	def sensor_one_setName_handle(self):
		board.set_sensor_name(1, str(self.sensor_one_name.text()))
		print self.sensor_one_name.text()
	def sensor_one_enable_handle(self):
		if(self.sensor_one_enable.isChecked()):
			board.enable_sensor(1)
		else:
			board.disable_sensor(1)


	def sensor_two_setName_handle(self):
		board.set_sensor_name(2, str(self.sensor_two_name.text()))
		print self.sensor_two_name.text()
	def sensor_two_enable_handle(self):
		if(self.sensor_two_enable.isChecked()):
			board.enable_sensor(2)
		else:
			board.disable_sensor(2)


	def sensor_three_setName_handle(self):
		board.set_sensor_name(3, str(self.sensor_three_name.text()))
		print self.sensor_three_name.text()
	def sensor_three_enable_handle(self):
		if(self.sensor_three_enable.isChecked()):
			board.enable_sensor(3)
		else:
			board.disable_sensor(3)


	def sensor_four_setName_handle(self):
		board.set_sensor_name(4, str(self.sensor_four_name.text()))
		print self.sensor_four_name.text()
	def sensor_four_enable_handle(self):
		if(self.sensor_four_enable.isChecked()):
			board.enable_sensor(4)
		else:
			board.disable_sensor(4)


app = QtGui.QApplication(sys.argv)
myWidget = MyWidget(None)
myWidget.show()
app.exec_()


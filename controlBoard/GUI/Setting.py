import sys
from PyQt4 import QtCore, QtGui, uic
import boardControlLib as b

board = b.BoardControlLib()

form_class = uic.loadUiType("Settings.ui")[0]

class MyWidget(QtGui.QMainWindow, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.initialize_card_button.clicked.connect(self.initialize_handle)
		self.start_logging_button.clicked.connect(self.start_logging_handle)
		self.stop_logging_button.clicked.connect(self.stop_logging_handle)
		self.save_setting_button.clicked.connect(self.save_setting_handle)

		self.file_save_button.clicked.connect(self.file_save_handle)
		self.file_load_button.clicked.connect(self.file_load_handle)

	def initialize_handle(self):
		print "Initializing"
		board.initialize_card()

	def start_logging_handle(self):
		board.start_logging()
		print "Start logging"

	def stop_logging_handle(self):
		board.stop_logging()
		print "Stopped Logging"

	def save_setting_handle(self):
		setFile = {0: board.set_CSV, 1: board.set_Binary}
		setFile[self.filetype.currentIndex()]()
		
		board.set_sample_rate(self.sample_rate.value())

		board.set_sensor_name(1, str(self.sensor_one_name.text()))
		print str(self.sensor_one_name.text())
		board.set_sensor_name(2, str(self.sensor_two_name.text()))
		print str(self.sensor_two_name.text())
		board.set_sensor_name(3, str(self.sensor_three_name.text()))
		print str(self.sensor_three_name.text())
		board.set_sensor_name(4, str(self.sensor_four_name.text()))
		print str(self.sensor_four_name.text())

		if(self.check_one.isChecked()):
			board.enable_sensor(1)
		else:
			board.disable_sensor(1)

		if(self.check_two.isChecked()):
			board.enable_sensor(2)
		else:
			board.disable_sensor(2)

		if(self.check_three.isChecked()):
			board.enable_sensor(3)
		else:
			board.disable_sensor(3)

		if(self.check_four.isChecked()):
			board.enable_sensor(4)
		else:
			board.disable_sensor(4)

	def file_save_handle(self):
		fname = QtGui.QFileDialog.getSaveFileName(self, 'Save As')
		if(len(fname) != 0):
			file_setting = open(fname, 'w')
			file_setting.write("channel_1_name " + self.sensor_one_name.text() + "\n");
			file_setting.write("channel_2_name " + self.sensor_two_name.text() + "\n");
			file_setting.write("channel_3_name " + self.sensor_three_name.text() + "\n");
			file_setting.write("channel_4_name " + self.sensor_four_name.text() + "\n");

			file_setting.write("channel_1_enabled " + str(self.check_one.isChecked()) + "\n")
			file_setting.write("channel_2_enabled " + str(self.check_two.isChecked()) + "\n")
			file_setting.write("channel_3_enabled " + str(self.check_three.isChecked()) + "\n")
			file_setting.write("channel_4_enabled " + str(self.check_four.isChecked()) + "\n")

			file_setting.write("sample_delay " + str(100000/self.sample_rate.value()) + "\n")

			fileformat = self.filetype.currentText()
			if(fileformat == "Binary"):
				fileformat = "raw"
			file_setting.write("file_format " + fileformat)

	def file_load_handle(self):
		fname = QtGui.QFileDialog.getOpenFileName(self, 'Load Settings')
		file_load = open(fname, 'r') 

		self.sensor_one_name.setText(file_load.readline().split(" ")[1].strip())
		self.sensor_two_name.setText(file_load.readline().split(" ")[1].strip())
		self.sensor_three_name.setText(file_load.readline().split(" ")[1].strip())
		self.sensor_four_name.setText(file_load.readline().split(" ")[1].strip())

		self.check_one.setChecked(file_load.readline().split(" ")[1].lower().strip() in ["true", "yes", "1"])
		self.check_two.setChecked(file_load.readline().split(" ")[1].lower().strip() in ["true", "yes", "1"])
		self.check_three.setChecked(file_load.readline().split(" ")[1].lower().strip() in ["true", "yes", "1"])
		self.check_four.setChecked(file_load.readline().split(" ")[1].lower().strip() in ["true", "yes", "1"])

		self.sample_rate.setValue(100000/int(file_load.readline().split(" ")[1]));

		filetype_in = file_load.readline().split(" ")[1].lower()
		if(filetype_in == "csv"):
			self.filetype.setCurrentIndex(0);
		elif(filetype_in == "raw"):
			self.filetype.setCurrentIndex(1);

app = QtGui.QApplication(sys.argv)
myWidget = MyWidget(None)
myWidget.show()
app.exec_()


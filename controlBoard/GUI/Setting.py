import sys
from PyQt4 import QtCore, QtGui, uic
import boardControlLib as b
import time
import configParse
import datetime

board = b.BoardControlLib()

form_class = uic.loadUiType("Settings.ui")[0]

class MyWidget(QtGui.QMainWindow, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.initialize_card_button.clicked.connect(self.initialize_handle)
		self.logging_button.clicked.connect(self.logging_handle)
		self.schedule_button.clicked.connect(self.schedule_button_handle)

		self.save_setting_button.clicked.connect(self.save_setting_handle)

		self.file_save_button.clicked.connect(self.file_save_handle)
		self.file_load_button.clicked.connect(self.file_load_handle)

		self.start_time.setDateTime(datetime.datetime.now())
		self.end_time.setDateTime(datetime.datetime.now())
		self.start_time.setEnabled(False);
		self.end_time.setEnabled(False);


	def initialize_handle(self):
		print "Initializing"
		board.initialize_card()

	def logging_handle(self):
		logging = (self.logging_button.text() == 'Stop Logging')
		if(not logging):
			board.start_logging()
			print "Start logging"
			self.logging_button.setText("Stop Logging")
		else:
			board.stop_logging()
			print "Stop logging"
			self.logging_button.setText("Start Logging")

	def schedule_button_handle(self):
		status = (self.schedule_button.text() == "Stop Scheduling")
		if(not status):
			board.enable_scheduling()
			self.start_time.setEnabled(True)
			self.end_time.setEnabled(True)
			print "Start Scheduling"
			self.schedule_button.setText("Stop Scheduling")
		else:
			board.disable_scheduling()
			self.start_time.setEnabled(False)
			self.end_time.setEnabled(False)
			print "Stop Scheduling"
			self.schedule_button.setText("Start Schedulng")

	def save_setting_handle(self):
<<<<<<< HEAD
		setFile = {0: board.set_CSV, 1: board.set_Raw}
=======
		setFile = {0: board.set_csv, 1: board.set_raw}
>>>>>>> 7500add07c67a40bba6199952f5b74b517e47834
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

		start = self.start_time.dateTime().toPyDateTime()
		end = self.end_time.dateTime().toPyDateTime()

		start_unix =  int(time.mktime(start.timetuple()))
		end_unix = int(time.mktime(end.timetuple()))

		print start_unix
		print end_unix

		board.set_scheduled_start(start_unix)
		board.set_scheduled_end(end_unix)


	def file_save_handle(self):
		fname = QtGui.QFileDialog.getSaveFileName(self, 'Save As')
		if(len(fname) != 0):
			file_setting = open(fname, 'w')
			file_setting.write("channel_1_name " + self.sensor_one_name.text() + "\n");
			file_setting.write("channel_2_name " + self.sensor_two_name.text() + "\n");
			file_setting.write("channel_3_name " + self.sensor_three_name.text() + "\n");
			file_setting.write("channel_4_name " + self.sensor_four_name.text() + "\n");

			if(self.check_one.isChecked()):
				file_setting.write("channel_1_enabled\n")
			if(self.check_two.isChecked()):
				file_setting.write("channel_2_enabled\n")
			if(self.check_three.isChecked()):
				file_setting.write("channel_3_enabled\n")
			if(self.check_four.isChecked()):
				file_setting.write("channel_4_enabled\n")

			file_setting.write("sample_delay " + str(100000/self.sample_rate.value()) + "\n")

			fileformat = self.filetype.currentText()
			file_setting.write("file_format " + fileformat + "\n")

			file_setting.write("start_time " + str(self.start_time.dateTime().toPyDateTime().strftime("%Y-%m-%d %H:%M:%S")) + "\n");
			file_setting.write("end_time " + str(self.end_time.dateTime().toPyDateTime().strftime("%Y-%m-%d %H:%M:%S")) + "\n");


			if(self.schedule_button.text() == "Stop Scheduling"): #currently logging
				file_setting.write("scheduling enabled")




	def file_load_handle(self):
		fname = QtGui.QFileDialog.getOpenFileName(self, 'Load Settings')
		configFile = open(fname, 'r')
		keyValueDict = configParse.fileToDic(configFile)
		for currentKey in keyValueDict.keys():
			currentValue = keyValueDict[currentKey]

			if(currentKey == "channel_1_name"):
				self.sensor_one_name.setText(currentValue)
			if(currentKey == "channel_2_name"):
				self.sensor_two_name.setText(currentValue)
			if(currentKey == "channel_3_name"):
				self.sensor_three_name.setText(currentValue)
			if(currentKey == "channel_4_name"):
				self.sensor_four_name.setText(currentValue)

			if(currentKey == "channel_1_enabled"):
				self.check_one.setChecked(True)
			if(currentKey == "channel_2_enabled"):
				self.check_two.setChecked(True)
			if(currentKey == "channel_3_enabled"):
				self.check_three.setChecked(True)
			if(currentKey == "channel_4_enabled"):
				self.check_four.setChecked(True)

			if(currentKey == "sample_delay"):
				self.sample_rate.setValue(100000.0/int(currentValue))

			if(currentKey == "file_format"):
				if(currentValue.lower() == 'csv'):
					self.filetype.setCurrentIndex(0)
				if(currentValue.lower() == 'raw'):
					self.filetype.setCurrentIndex(1)

			if(currentKey == "scheduling_enable"):
				if(self.schedule_button.text() == "Stop Scheduling"):
					pass #currently scheduling
				else:
					schedule_button_handle()

			if(currentKey == "start_time"):
				currentDate = "".join((currentValue.split(" ")[0]).split("-"))
				self.start_time.setDate(QtCore.QDate.fromString(currentDate, "yyyyMMdd"))
				currentTime = "".join((currentValue.split(" ")[1]).split(":"))
				self.start_time.setTime(QtCore.QTime.fromString(currentTime, "HHmmss"))

			if(currentKey == "end_time"):
				currentDate = "".join((currentValue.split(" ")[0]).split("-"))
				self.end_time.setDate(QtCore.QDate.fromString(currentDate, "yyyyMMdd"))
				currentTime = "".join((currentValue.split(" ")[1]).split(":"))
				self.end_time.setTime(QtCore.QTime.fromString(currentTime, "HHmmss"))


app = QtGui.QApplication(sys.argv)
myWidget = MyWidget(None)
myWidget.show()
app.exec_()


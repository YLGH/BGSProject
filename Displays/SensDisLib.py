from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
from collections import deque
import spidev
import threading
import time


class SensorDisplay:

	def __init__(self, displayTime = 2):
		#input is the maxDisplayTime in seconds
		self.numSensors = 0

		self.spi = spidev.SpiDev()
		self.spi.open(0,0)

		maxlenx = displayTime * 1000
		self.data = [deque(maxlen=maxlenx),deque(maxlen=maxlenx),deque(maxlen=maxlenx),deque(maxlen=maxlenx)]
		self.qx = deque(maxlen=maxlenx)

		self.app = QtGui.QApplication([])
		self.win = pg.GraphicsWindow(title = "Sensor Displays")
		self.win.resize(1000, 800)
		self.win.setWindowTitle('Sensor Displays')

		self.sensorSet = [False, False, False, False]

		pg.setConfigOptions(antialias = False)

	#Add Sensor One

	def add_Sensor_One(self, graphTitle = "Sensor One"):
		if(not self.sensorSet[0]):
			if self.numSensors == 2:
				win.nextRow()

			self.p1 = self.win.addPlot(title = graphTitle)
			self.p1.setYRange(0, 4096) #default Y range
			self.curve1 = self.p1.plot(pen = 'r')
			self.numSensors += 1

			self.sensorSet[0] = True

	def add_Sensor_Two(self, graphTitle = "Sensor Two"):
		if(not self.sensorSet[1]):
			if self.numSensors == 2:
				self.win.nextRow()

			self.p2 = self.win.addPlot(title = graphTitle)
			self.p2.setYRange(0, 4096)
			self.curve2 = self.p2.plot(pen = 'g')
			self.numSensors += 1

			self.sensorSet[1] = True

	def add_Sensor_Three(self, graphTitle = "Sensor Three"):
		if(not self.sensorSet[2]):
			if self.numSensors == 2:
				self.win.nextRow()

			self.p3 = self.win.addPlot(title = graphTitle)
			self.p3.setYRange(0, 4096)
			self.curve3 = self.p3.plot(pen = 'b')
			self.numSensors += 1

			self.sensorSet[2] = True

	def add_Sensor_Four(self, graphTitle = "Sensor Four"):
		if(not self.sensorSet[3]):
			if self.numSensors == 2:
				self.win.nextRow()

			self.p4 = self.win.addPlot(title = graphTitle)
			self.p4.setYRange(0, 4096)
			self.curve4 = self.p4.plot(pen = 'y')
			self.numSensors += 1

			self.sensorSet[3] = True

	def setYRange_Sensor_One(self, low, high):
		self.p1.setYRange(low, high);

	def setYRange_Sensor_Two(self, low, high):
		self.p2.setYRange(low, high);

	def setYRange_Sensor_Three(self, low, high):
		self.p3.setYRange(low, high);

	def setYRange_Sensor_Four(self, low, high):
		self.p4.setYRange(low, high);

	def update(self):
		if(self.sensorSet[0]):
			self.curve1.setData(self.qx,self.data[0])
		if(self.sensorSet[1]):
			self.curve2.setData(self.qx,self.data[1])
		if(self.sensorSet[2]):
			self.curve3.setData(self.qx, self.data[2])
		if(self.sensorSet[3]):
			self.curve4.setData(self.qx,self.data[3])

	def getNext(self):
		ptr = 0

		while True:
			time.sleep(.0001)
			byteArray = self.spi.xfer([0x01])	
			byteArray = self.spi.xfer([0xff]*8)
			for i in range(0, 4):
				toAdd = (byteArray[(2*i)] << 8) + byteArray[(2*i)+1]
				self.data[i].append(toAdd)
			self.qx.append(ptr)
			ptr+=1

	def run(self):
		self.input_Thread = threading.Thread(target = self.getNext)
		self.input_Thread.daemon = True
		self.input_Thread.start()

		self.timer = QtCore.QTimer()
		self.timer.timeout.connect(self.update)
		self.timer.start()

		import sys
		if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
			QtGui.QApplication.instance().exec_()









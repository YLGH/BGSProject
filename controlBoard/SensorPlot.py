from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
from collections import deque
import spidev
import threading
import time
import Sensor


class SensorPlot:

	def __init__(self, displayTime = 10):
		#input is the maxDisplayTime in seconds
		self.numSensors = 0

		self.spi = spidev.SpiDev()
		self.spi.open(0,0)

		maxlength = displayTime * 1000
		self.data = [deque(maxlen=maxlength),deque(maxlen=maxlength),deque(maxlen=maxlength),deque(maxlen=maxlength)]
		self.qx = deque(maxlen=maxlength)

		self.app = QtGui.QApplication([])
		self.win = pg.GraphicsWindow(title = "Sensor Readings")
		self.win.resize(1000, 800)
		self.win.setWindowTitle('Sensor Plots')

		self.sensors = [Sensor.Sensor(), Sensor.Sensor(), Sensor.Sensor(), Sensor.Sensor()]
		self.plot = [None, None, None, None]
		self.curve = [None, None, None, None]

		self.colors = ['r','g','b','y']


		pg.setConfigOptions(antialias = False)

	
	def add_sensor(self, index, graphTitle = "New Sensor"):
		index -= 1;
		assert(not self.sensors[index].toLog), "This sensor is already added!"

		if(self.numSensors == 2):
			self.win.nextRow()
		self.sensors[index].start_logging()

		self.plot[index] = self.win.addPlot(title = graphTitle)
		self.plot[index].setYRange(0, 4096)
	
		self.curve[index] = self.plot[index].plot(pen = self.colors[index])

		self.numSensors += 1

	def setYRange_sensor(self, index, low, high):
		assert(low <= high), "The lower bound must be less than the higher bound!"
		self.plot[index-1].setYRange(low, high)

	def update(self):
		for i in range(0, 4):
			if(self.sensors[i].toLog):
				self.curve[i].setData(self.qx, self.data[i])

	def getNext(self):
		ptr = 0
		time.sleep(.0001)
		while True:
			time.sleep(.0000001)
			byteArray = self.spi.xfer([0x01])#sending a "I need data bit"
			byteArray = self.spi.xfer([0xff]*8) #retrieving the 8 bits
			for i in range(0, 4):
				if(self.sensors[i].toLog):
					toAdd = (byteArray[(2*i)] << 8) + byteArray[(2*i)+1]
					self.data[i].append(toAdd)
			self.qx.append(ptr)
			ptr+=1


	def runPlot(self):
		self.input_Thread = threading.Thread(target = self.getNext)
		self.input_Thread.daemon = True
		self.input_Thread.start()

		self.timer = QtCore.QTimer()
		self.timer.timeout.connect(self.update)
		self.timer.start()

		import sys
		if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
			QtGui.QApplication.instance().exec_()


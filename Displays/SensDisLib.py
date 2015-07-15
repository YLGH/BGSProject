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
		numSensors = 0

		spi = spidev.SpiDev()
		spi.open(0,0)

		maxlength = displayTime * 1000
		data = [deque(maxlen=maxlenx),deque(maxlen=maxlenx),deque(maxlen=maxlenx),deque(maxlen=maxlenx)]
		qx = deque(maxlen=maxlenx)

		app = QtGui.QApplication([])
		win = pg.GraphicsWindow(title = "Sensor Displays")
		win.resize(1000, 800)
		win.setWindowTitle('Sensor Displays')

		sensorSet = [False, False, False, False]

		pg.setConfigOptions(antialias = False)

	#Add Sensor One

	def add_Sensor_One(self, graphTitle = "Sensor One"):
		if(not sensorSet[0]):
			if numSensors == 2:
				win.nextRow()

			p1.win.addPlot(title = graphTitle)
			p1.setYRange(0, 4096) #default Y range
			curve1 = p1.plot(pen = 'r')
			numSensors += 1

			sensorSet[0] = True

	def add_Sensor_Two(self, graphTitle = "Sensor Two"):
		if(not sensorSet[1]):
			if numSensors == 2:
				win.nextRow()

			p2.win.addPlot(title = graphTitle)
			p2.setYRange(0, 4096)
			curve2 = p2.plot(pen = 'b')
			numSensors += 1

			sensorSet[1] = True

	def add_Sensor_Three(self, graphTitle = "Sensor Three"):
		if(not sensorSet[2]):
			if numSensors == 2:
				win.nextRow()

			p3.win.addPlot(title = graphTitle)
			p3.setYRange(0, 4096)
			curve3 = p3.plot(pen = 'g')
			numSensors += 1

			sensorSet[2] = True

	def add_Sensor_Four(self, graphTitle = "Sensor Four"):
		if(not sensorSet[3]):
			if numSensors == 2:
				win.nextRow()

			p4.win.addPlot(title = graphTitle)
			p4.setYRange(0, 4096)
			curve4 = p4.plot(pen = 'y')
			numSensors += 1

			sensorSet[3] = True

	def setYRange_Sensor_One(self, low, high):
		p1.setYRange(low, high);

	def setYRange_Sensor_Two(self, low, high):
		p2.setYRange(low, high);

	def setYRange_Sensor_Three(self, low, high):
		p3.setYRange(low, high);

	def setYRange_Sensor_Four(self, low, high):
		p4.setYRange(low, high);

	def update():
		global curve1, curve2, curve3, curve4, ptr, p1, p2, p3, p4, qx, data
		if(sensorSet[0]):
			curve1.setData(qx, data[0])
		if(sensorSet[1]):
			curve2.setData(qx, data[1])
		if(sensorSet[2]):
			curve3.setData(qx, data[2])
		if(sensorSet[3]):
			curve4.setData(qx, data[3])

	def getNext():
		global ptr
		ptr = 0

		while True:
			time.sleep(.0001)
			byteArray = spi.xfer([0x01])	
			byteArray = spi.xfer([0xff]*8)
			for i in range(0, 4):
				toAdd = (byteArray[(2*i)] << 8) + byteArray[(2*i)+1]
				data[i].append(toAdd)
				qx.append(ptr)
			ptr+=1

	def run():
		input_Thread = threading.Thread(target = getNext)
		input_Thread.daemon = True
		input_Thread.start()

		timer = QtCore.QTimer()
		timer.timeout.connect(update)
		timer.start()

		import sys
		if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
			QtGui.QApplication.instance().exec_()









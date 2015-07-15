from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
from collections import deque
import spidev
import threading

#QtGui.QApplication.setGraphicsSystem('raster')

spi = spidev.SpiDev();
spi.open(0,0);

q = [deque(maxlen=1000),deque(maxlen=1000),deque(maxlen=1000),deque(maxlen=1000)]
qx = deque(maxlen=1000)

def getNext():
    global ptr
    ptr = 0

    while True:
        byteArray = spi.xfer([0xff]*2);
        for i in range(0, 4):
            toAdd = (byteArray[0] << 8) + byteArray[1]
            q[i].append(toAdd)
        qx.append(ptr)
        ptr+=1

input_Thread = threading.Thread(target = getNext)
input_Thread.start();

app = QtGui.QApplication([])
win = pg.GraphicsWindow(title="Sensor Plots")
win.resize(1000,800)
win.setWindowTitle('Sensor plots')

# Enable antialiasing for prettier plots
pg.setConfigOptions(antialias=True)


p1 = win.addPlot(title="Sensor One")
curve1=p1.plot(pen='r')
def update1():
    global curve1, p1
    curve1.setData(qx, data[0])

p2 = win.addPlot(title="Sensor Two")
curve2 = p2.plot(pen = 'g')
def update2():
    global curve2, p2
    curve2.setData(qx, data[1])

win.nextRow()

p3 = win.addPlot(title="Sensor Three")
curve3 = p3.plot(pen = 'b')
def update3():
    global curve3, p3
    curve3.setData(qx, data[2])

p4 = win.addPlot(title="Sensor Four")
curve4 = p4.plot(pen='y')
ptr = 0
def update4():
    global curve4, data, ptr, p4
    curve4.setData(qx, data[3])

def update():
    global curve1, curve2, curve3, curve4, ptr, p1, p2, p3, p4, qx
    update1()
    update2()
    update3()
    update4()

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start()

if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()

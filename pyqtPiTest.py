from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
import time
from collections import deque
import spidev


app = QtGui.QApplication([])
win = pg.GraphicsWindow(title="Seismic Testing")
win.resize(1000,600)
win.setWindowTitle('Seismic Test')

pg.setConfigOptions(antialias=False)
p6 = win.addPlot()
curve = p6.plot(pen='y')

ptr = 0


spi = spidev.SpiDev();
spi.open(0,0);

q = deque(maxlen = 200);
qx = deque(maxlen = 200);

def getNext():
	byteArray= spi.xfer([0xff]*2);
	q.append((byteArray[0] << 8) + byteArray[1]);

def update():
    global curve, data, ptr, p6
    getNext();
    qx.append(ptr);
    curve.setData(qx, q);
    ptr += 1

timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start()

if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()

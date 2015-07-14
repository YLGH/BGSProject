from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
import time
from collections import deque
import spidev
import threading



app = QtGui.QApplication([])
win = pg.GraphicsWindow(title="Seismic Testing")
win.resize(1000,600)
win.setWindowTitle('Seismic Test')

pg.setConfigOptions(antialias=False)
p6 = win.addPlot()
curve = p6.plot(pen='y')

spi = spidev.SpiDev();
spi.open(0,0);

q = deque(maxlen = 200);
qx = deque(maxlen = 200);

def getNext():
        global i;
        i = 0;
        while True:
            byteArray= spi.xfer([0xff]*2);
            q.append((byteArray[0] << 8) + byteArray[1]);
            qx.append(i);
            i += 1;

a = threading.Thread(target= getNext);
a.start();

def update():
    global curve, data, p6
    curve.setData(qx, q);


timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start()

if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()

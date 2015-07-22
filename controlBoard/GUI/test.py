import sys
from PyQt4 import QtCore, QtGui, uic

form_class = uic.loadUiType("testlayout.ui")[0]

class MyWindowClass(QtGui.QMainWindow, form_class):
	def __init__(self, parent = None):
		QtGui.QMainWindow.__init__(self, parent)
		self.setupUi(self)
		self.cmdClear.clicked.connect(self.cmdClear_handle)

	def cmdClear_handle(self):
		print "test"




app = QtGui.QApplication(sys.argv)
myWindow = MyWindowClass(None)
myWindow.show()
app.exec_()
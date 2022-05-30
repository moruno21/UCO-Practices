import sys
from PyQt5 import QtWidgets
import vista as vista

app = QtWidgets.QApplication(sys.argv)
form = vista.Editor()
sys.exit(app.exec_())

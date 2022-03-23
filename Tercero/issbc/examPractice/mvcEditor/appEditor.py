# -*- coding: utf-8 -*-

import sys
from PyQt5 import QtWidgets
import vistaEditor as vista

app = QtWidgets.QApplication(sys.argv) #Crea una aplicacion
form = vista.Editor()   #Crea una instancia del formulario
sys.exit(app.exec_())   #Se inicia la aplicacin y se espera eventos

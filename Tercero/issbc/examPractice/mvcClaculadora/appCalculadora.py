# -*- coding: utf-8 -*-
"""
Created on Tue Nov 18 11:48:33 2014

@author: acalvo
"""
import sys
from PyQt5 import QtWidgets
import ckVtsCalculadora as vts

app = QtWidgets.QApplication(sys.argv) #Crea una aplicacion
form = vts.CalculadoraDlg()   #Crea una instancia del formulario
sys.exit(app.exec_())   #Se inicia la aplicacin y se espera eventos

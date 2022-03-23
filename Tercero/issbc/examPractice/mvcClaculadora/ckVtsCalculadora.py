#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
"""
Created on Sat Jan 18 11:29:53 2014

@author: acalvo
"""


import sys
from PyQt5 import QtCore
from PyQt5 import QtWidgets
import ckControladorCalculadora as ctrl

from PyQt5.QtWidgets import QWidget, QCheckBox, QApplication
#from PyQt5.QtCore import Qt
import sys

class CalculadoraDlg(QWidget):
    def __init__(self):
        super(CalculadoraDlg, self).__init__()
        
        #Label Se crean las etiquetas
        labelPrimerDato=QtWidgets.QLabel("A:",self)  
        labelSegundoDato=QtWidgets.QLabel("B:",self)
        labelResultadoDato=QtWidgets.QLabel("R:",self)
        #labelOperador=QtGui.QLabel(u"Operacion",self)
        
        #Entradas Se crean los controles para la entrada de datos
        self.aEdit = QtWidgets.QLineEdit()
        self.bEdit = QtWidgets.QLineEdit()
        self.rEdit = QtWidgets.QLineEdit()
        self.explicacionEdit=QtWidgets.QLineEdit()
       
        #Botones 
        self.sumaButtom=QtWidgets.QPushButton('+')
        self.restaButtom=QtWidgets.QPushButton('-')
        self.productoButtom=QtWidgets.QPushButton('*') 
        self.divisionButtom=QtWidgets.QPushButton('/')
        self.moduloButtom=QtWidgets.QPushButton('M')
        
        #Se crea un gestor de distribución de controles horizontal
        self.buttomsLayout = QtWidgets.QHBoxLayout()
        self.buttomsLayout.addStretch()
        # Ver http://stackoverflow.com/questions/20452754/how-exactly-does-addstretch-work-in-qboxlayout
        # Ver https://qt-project.org/doc/qt-4.8/layout.html
        self.buttomsLayout.addWidget(self.sumaButtom)
        self.buttomsLayout.addWidget(self.restaButtom)
        self.buttomsLayout.addWidget(self.productoButtom)
        self.buttomsLayout.addWidget(self.divisionButtom)
        self.buttomsLayout.addWidget(self.moduloButtom)
        self.buttomsLayout.addStretch()
        
        #Rejilla de distribución de los controles
        grid = QtWidgets.QGridLayout()
        grid.setSpacing(5)
        grid.addWidget(labelPrimerDato, 0, 0)
        grid.addWidget(self.aEdit, 0, 1)
        grid.addWidget(labelSegundoDato, 1, 0)
        grid.addWidget(self.bEdit, 1, 1)
        grid.addWidget(labelResultadoDato, 2, 0)
        grid.addWidget(self.rEdit, 2, 1)
        grid.addWidget(self.explicacionEdit,3,0,1,2)


        #Diseño principal de distribución de controles
        mainLayout = QtWidgets.QVBoxLayout()
        mainLayout.addLayout(grid)
        mainLayout.addLayout(self.buttomsLayout)
        
        self.setLayout(mainLayout)
        
    
        self.setGeometry(150, 100, 100, 100)
        self.setWindowTitle(u"CALCULADORA")
        self.show()
 
        #self.center()
        #Conexiones:
        #==========
        self.sumaButtom.clicked.connect(self.sumar)
        self.restaButtom.clicked.connect(self.restar)
        self.productoButtom.clicked.connect(self.multiplicar)
        self.divisionButtom.clicked.connect(self.dividir)
        self.moduloButtom.clicked.connect(self.modulo)

    #
    def getDatos(self):
        self.explicacionEdit.clear()
        a=float(self.aEdit.text())
        b=float(self.bEdit.text())
        return a,b

    def sumar(self):
        a,b=self.getDatos()
        r=ctrl.eventSumar(a,b)
        self.rEdit.setText(str(r))

    def restar(self):
        
        a,b=self.getDatos()
        r=ctrl.eventRestar(a,b)
        self.rEdit.setText(str(r))
         

    def multiplicar(self):
        a,b=self.getDatos()
        r=ctrl.eventMultiplicar(a,b)
        self.rEdit.setText(str(r))
         
    def dividir(self):
        a,b=self.getDatos()
        r=ctrl.eventDividir(a,b)
        if not r==None:
            self.rEdit.setText(str(r))
        else:
            self.rEdit.clear()
            self.explicacionEdit.setText('División por cero')
            
    def modulo(self):
        a,b=self.getDatos()
        r=ctrl.eventModulo(a,b)
        self.rEdit.setText(str(r))
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = CalculadoraDlg()
    sys.exit(app.exec_())


 
#!/usr/bin/python

import sys
from PyQt5.QtWidgets import (
    QWidget, QPushButton, QApplication, QLabel, QGridLayout, QTextEdit, QLineEdit, QListWidget, QHBoxLayout, QVBoxLayout, QMessageBox)

import controllerapp as controller


class Editor(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        self.filePath = None

        grid = QGridLayout()
        grid.setSpacing(10)

        labelPrimerDato = QLabel("Nombre:", self)
        labelSegundoDato = QLabel("Apellidos:", self)
        labelCalificacion = QLabel("Calificacion:", self)

        self.nombreEdit = QLineEdit()
        self.apellidosEdit = QLineEdit()
        self.calificacionEdit = QLineEdit()
        self.textArea = QTextEdit()
        self.listWidget = QListWidget()

        # Botones
        self.addAlumnoButton = QPushButton('Añadir alumno')
        self.aprobadosButton = QPushButton('Alumnos aprobados')
        self.mediaButton = QPushButton('Media calificaciones')
        self.openButton = QPushButton('Abrir fichero')
        self.saveButton = QPushButton('Guardar fichero')

        self.buttomsLayout = QHBoxLayout()
        self.buttomsLayout.addStretch()
        # Ver http://stackoverflow.com/questions/20452754/how-exactly-does-addstretch-work-in-qboxlayout
        # Ver https://qt-project.org/doc/qt-4.8/layout.html
        self.buttomsLayout.addWidget(self.addAlumnoButton)
        self.buttomsLayout.addWidget(self.aprobadosButton)
        self.buttomsLayout.addWidget(self.mediaButton)
        self.buttomsLayout.addWidget(self.openButton)
        self.buttomsLayout.addWidget(self.saveButton)
        self.buttomsLayout.addStretch()

        grid = QGridLayout()
        grid.setSpacing(5)
        grid.addWidget(labelPrimerDato, 0, 0)
        grid.addWidget(self.nombreEdit, 0, 1)
        grid.addWidget(labelSegundoDato, 1, 0)
        grid.addWidget(self.apellidosEdit, 1, 1)
        grid.addWidget(labelCalificacion, 2, 0)
        grid.addWidget(self.calificacionEdit, 2, 1)
        grid.addWidget(self.textArea, 3, 1, 5, 1)
        grid.addWidget(self.listWidget, 9, 1, 3, 1)
        mainLayout = QVBoxLayout()
        mainLayout.addLayout(grid)
        mainLayout.addLayout(self.buttomsLayout)

        self.setLayout(mainLayout)
        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle('Editor de textos')
        self.show()

        self.addAlumnoButton.clicked.connect(self.addDatosLista)
        self.aprobadosButton.clicked.connect(self.getAprobados)
        self.openButton.clicked.connect(self.openFileDialog)
        self.saveButton.clicked.connect(self.fileSave)
        self.mediaButton.clicked.connect(self.getMedia)

        self.sumaCalificaciones = 0
        self.sumaAlumnos = 0
        self.alumnosAprobados = []

    def openFileDialog(self):
        controller.openFileDialog(self)

    def fileSave(self):
        controller.fileSave(self)

    def fileSaveToPath(self):
        controller.fileSaveToPath(self)

    def getDatos(self):
        nombre = self.nombreEdit.text()
        apellidos = self.apellidosEdit.text()
        calificacion = self.calificacionEdit.text()
        self.sumaCalificaciones += float(calificacion)
        self.sumaAlumnos += 1
        if float(calificacion) >= 5.0:
            self.alumnosAprobados.append(nombre)

        return nombre, apellidos, calificacion

    def addDatosLista(self):
        a, b, c = self.getDatos()
        controller.addDatosLista(a, b, c, self)

    def getMedia(self):
        media = controller.calculateMedia(self)
        reply = QMessageBox.information(
            self, "Info", f'La media es {media}')

    def getAprobados(self):
        reply = QMessageBox.information(
            self, "Info", f'El número de aprobados es {len(self.alumnosAprobados)} y sus nombres son {self.alumnosAprobados}')


def main():
    app = QApplication(sys.argv)
    ex = Editor()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

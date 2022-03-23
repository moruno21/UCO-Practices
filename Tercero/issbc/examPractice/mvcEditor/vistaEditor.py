#!/usr/bin/python

import sys
from PyQt5.QtWidgets import (
    QWidget, QPushButton, QApplication, QLabel, QGridLayout, QTextEdit)

import controllerEditor as controller


class Editor(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        self.filePath = None

        grid = QGridLayout()
        grid.setSpacing(10)

        # folder stuff
        controller.treeAndListView(self)

        # texto 'carpeta' e input para especificar la carpeta
        folderText = QLabel('Carpeta')

        # area de texto
        self.textArea = QTextEdit()

        # set de botones laterales
        folderButton = QPushButton("Carpeta")
        openFileButton = QPushButton("Abrir archivo")
        saveButton = QPushButton("Salvar")
        saveAsButton = QPushButton("Salvar como")
        exitButton = QPushButton("Salir")

        # -- addWidgets to grid --
        # tree and list view
        grid.addWidget(self.treeview, 1, 0)
        grid.addWidget(self.listview, 2, 0)
        # folder text and area text
        grid.addWidget(folderText, 0, 0)
        grid.addWidget(self.textArea, 1, 1, 5, 1)
        # buttons
        grid.addWidget(folderButton, 0, 2)
        grid.addWidget(openFileButton, 1, 2)
        grid.addWidget(saveButton, 2, 2)
        grid.addWidget(saveAsButton, 3, 2)
        grid.addWidget(exitButton, 5, 2)

        self.setLayout(grid)
        self.setGeometry(300, 300, 300, 150)
        self.setWindowTitle('Editor de textos')
        self.show()

        # configuración de los botones
        exitButton.clicked.connect(QApplication.instance().quit)
        openFileButton.clicked.connect(self.openFileDialog)
        saveAsButton.clicked.connect(self.fileSaveAs)
        saveButton.clicked.connect(self.fileSave)

    def openFileDialog(self):
        controller.openFileDialog(self)

    def onFolderClicked(self, index):
        controller.onFolderClicked(self, index)

    def fileSaveAs(self):
        controller.fileSaveAs(self)

    def fileSave(self):
        controller.fileSave(self)

    def fileSaveToPath(self):
        controller.fileSaveToPath(self)


def main():
    app = QApplication(sys.argv)
    ex = Editor()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

import sys
from PyQt5.QtWidgets import QMainWindow, QAction, QTextEdit, QFileDialog, QApplication
from PyQt5 import QtGui, QtCore


class Main(QMainWindow):

    def __init__(self):
        QMainWindow.__init__(self)
        self.initUI()

    def initUI(self):

        newAction = QAction('Nuevo', self)
        newAction.setShortcut('Ctrl+N')
        newAction.triggered.connect(self.newFile)

        saveAction = QAction('Guardar', self)
        saveAction.setShortcut('Ctrl+S')
        saveAction.triggered.connect(self.saveFile)

        openAction = QAction('Abrir', self)
        openAction.setShortcut('Ctrl+O')
        openAction.triggered.connect(self.openFile)

        menubar = self.menuBar()
        fileMenu = menubar.addMenu('Archivo')
        fileMenu.addAction(newAction)
        fileMenu.addAction(saveAction)
        fileMenu.addAction(openAction)

        self.txt = QTextEdit(self)
        self.setCentralWidget(self.txt)

        self.setGeometry(300, 300, 300, 300)
        self.setWindowTitle("Editor de textos")
        self.show()

    def newFile(self):
        self.txt.clear()

    def saveFile(self):
        filename = QFileDialog.getSaveFileName(self, 'Guardar Archivo')
        f = open(filename[0], 'w')
        filedata = self.txt.toPlainText()
        f.write(filedata)
        f.close()

    def openFile(self):
        filename = QFileDialog.getOpenFileName(self, 'Abrir Archivo')
        f = open(filename[0], 'r')
        filedata = f.read()
        self.txt.setText(filedata)
        f.close()


def main():
    app = QApplication(sys.argv)
    main = Main()
    main.show()

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

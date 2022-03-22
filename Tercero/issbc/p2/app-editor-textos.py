from PyQt5.QtWidgets import *
from PyQt5.QtGui import QIcon
import sys
from pathlib import Path


class Editor_texto(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.path = None
        self.txt = QTextEdit()
        self.setCentralWidget(self.txt)
        self.statusBar()

        newFile = QAction("Nuevo", self)
        newFile.setShortcut("Ctrl+N")
        newFile.setStatusTip("Nuevo archivo")
        newFile.triggered.connect(self.newFile)

        openFile = QAction("Abrir", self)
        openFile.setShortcut("Ctrl+O")
        openFile.setStatusTip("Abrir archivo")
        openFile.triggered.connect(self.openFile)

        saveFile = QAction("Guardar", self)
        saveFile.setShortcut("Ctrl+S")
        saveFile.setStatusTip("Guardar Archivo")
        saveFile.triggered.connect(self.saveFile)

        saveAsFile = QAction("Guardar como", self)
        saveAsFile.setShortcut("F12")
        saveAsFile.setStatusTip("Guardar como")
        saveAsFile.triggered.connect(self.saveAsFile)

        menubar = self.menuBar()
        fileMenu = menubar.addMenu("&Archivo")
        fileMenu.addAction(newFile)
        fileMenu.addAction(openFile)
        fileMenu.addAction(saveFile)
        fileMenu.addAction(saveAsFile)

        self.setGeometry(300, 300, 500, 500)
        self.setWindowTitle("Editor de texto")
        self.show()

    def newFile(self):
        self.txt.clear()

    def openFile(self):
        home_dir = str(Path.home())
        fname = QFileDialog.getOpenFileName(self, "Abrir archivo", home_dir)
        if fname[0]:
            f = open(fname[0], "r")
            with f:
                data = f.read()
                self.txt.setText(data)
                self.path = fname
                self.setWindowTitle(fname[0])

    def saveFile(self):
        if self.path is None:
            return self.saveAsFile()
        self.save_path()

    def saveAsFile(self):
        fname = QFileDialog.getSaveFileName(self, "Guardar archivo")
        if fname[0]:
            f = open(fname[0], "w")
            with f:
                data = self.txt.toPlainText()
                f.write(data)
                f.close()
                self.path = fname
                self.setWindowTitle(fname[0])

    def save_path(self):
        text = self.txt.toPlainText()
        with open(self.path[0], "w") as f:
            f.write(text)


def main():
    app = QApplication(sys.argv)
    ex = Editor_texto()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

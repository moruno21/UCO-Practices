from PyQt5.QtWidgets import (
    QFileDialog, QTreeView, QListView, QFileSystemModel)
from PyQt5.QtCore import (QDir)
from pathlib import Path


def openFileDialog(self):
    home_dir = str(Path.home())
    fname = QFileDialog.getOpenFileName(self, 'Abrir archivo', home_dir)
    self.setWindowTitle(fname[0])
    if fname[0]:
        f = open(fname[0], 'r')
        with f:
            data = f.read()
            self.textArea.setText(data)
            self.filePath = fname


def fileSave(self):
    if self.filePath is None:
        return self.fileSaveAs()
    self.fileSaveToPath()


def fileSaveToPath(self):
    text = self.textArea.toPlainText()
    with open(self.filePath[0], 'w') as f:
        f.write(text)


def addDatosLista(a, b, c, self):
    self.listWidget.addItem(a)
    self.listWidget.addItem(b)
    self.listWidget.addItem(c)


def calculateMedia(self):
    media = self.sumaCalificaciones / self.sumaAlumnos
    return media

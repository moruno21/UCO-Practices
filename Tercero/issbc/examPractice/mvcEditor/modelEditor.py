# -*- coding: utf-8 -*-


from PyQt5.QtWidgets import QFileDialog, QTreeView, QListView, QFileSystemModel
from PyQt5.QtCore import QDir
from pathlib import Path


def openFileDialog(self):
    home_dir = str(Path.home())
    fname = QFileDialog.getOpenFileName(self, "Open file", home_dir)
    self.setWindowTitle(fname[0])
    if fname[0]:
        f = open(fname[0], "r")
        with f:
            data = f.read()
            self.textArea.setText(data)
            self.filePath = fname


def onFolderClicked(self, index):
    path = self.dirModel.fileInfo(index).absoluteFilePath()
    self.listview.setRootIndex(self.fileModel.setRootPath(path))


def fileSaveAs(self):
    fname = QFileDialog.getSaveFileName(
        self,
        "Save file",
    )
    self.setWindowTitle(fname[0])
    if fname[0]:
        f = open(fname[0], "w")
        with f:
            data = self.textArea.toPlainText()
            f.write(data)
            f.close()
            self.filePath = fname


def fileSave(self):
    if self.filePath is None:
        return self.fileSaveAs()
    self.fileSaveToPath()


def fileSaveToPath(self):
    text = self.textArea.toPlainText()
    with open(self.filePath[0], "w") as f:
        f.write(text)


def treeAndListView(self):
    self.treeview = QTreeView()
    self.listview = QListView()
    path = QDir.rootPath()
    self.dirModel = QFileSystemModel()
    self.dirModel.setRootPath(QDir.rootPath())
    self.dirModel.setFilter(QDir.NoDotAndDotDot | QDir.AllDirs)
    self.fileModel = QFileSystemModel()
    self.fileModel.setFilter(QDir.NoDotAndDotDot | QDir.Files)
    self.treeview.setModel(self.dirModel)
    self.listview.setModel(self.fileModel)
    self.treeview.setRootIndex(self.dirModel.index(path))
    self.listview.setRootIndex(self.fileModel.index(path))
    self.treeview.clicked.connect(self.onFolderClicked)

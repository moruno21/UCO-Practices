# Modelo de la p3 ISSBC

from PyQt5.QtWidgets import QFileDialog
from pathlib import Path
import os.path


# Buscamos el path del archivo y los abrimos en modo lectura, para luego devolverlos todos
def doubleClickedTreeView(self, index):
    item = self.fileSystemModel.index(index.row(), 0, index.parent())  # Lo usaremos para obtener el path en la siguiente línea
    self.fileName[0] = self.fileSystemModel.filePath(item)  # Obtenemos el path del fichero o directorio

    if os.path.isdir(self.fileName[0]) == False:  # Si el path no es un directorio, lo abrimos (es un archivo)
        f = open(self.fileName[0], "r")  # Abrimos el fichero
        with f:
            data = f.read()  # Leemos el fichero
            return data  # Devolvemos el contenido


# Abrimos la carpeta para mostrarla en la sección de archivo
def openFolder(self):
    folder = str(QFileDialog.getExistingDirectory(self, "Select Directory"))  # Pasamos a cadena el path del directorio
    return folder  # Lo devolvemos


# Guarda el archivo
def saveFile(self):
    if self.fileName == ["Editor de texto", ".txt"]:  # Si editamos un texto que no existe y lo intentamos guardar, nos enviará a guardar como
        saveAsFile(self)  # Guardar como
    else:
        f = open(self.fileName[0], "w")  # Abrimos el fichero
        filedata = self.textEdit.toPlainText()  # Obtenemos el contenido del cuadro de texto
        f.write(filedata)  # Escribimos el contenido del cuadro de texto en el archivo
        f.close()  # Cerramos el archivo


# Guardar como un archivo
def saveAsFile(self):
    home = str(Path.home())  # Obtenemos el home para usarlo de raiz en la ventana de guardar como
    newFileName = QFileDialog.getSaveFileName(self, "Save File", home)  # Ventana emergente que permite guardar como
    if newFileName[0]:  # Si hemos introducido un nombre de archivo para así guardar como
        self.fileName = newFileName  # Establecemos el nombre del archivo
        f = open(self.fileName[0], "w")  # Abrimos el archivo
        filedata = self.textEdit.toPlainText()  # Obtenemos el contenido del cuadro de texto
        f.write(filedata)  # Escribimos el contenido del cuadro de texto en el archivo
        f.close()  # Cerramos el archivo

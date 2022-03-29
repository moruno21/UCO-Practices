# Vista de la p3 ISSBC

import sys
import controller as controller

from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QLineEdit, QPushButton, QTextEdit, QMessageBox, QVBoxLayout, QHBoxLayout, QGridLayout, QFileSystemModel, QTreeView


class EditorTextosDlg(QWidget):
    def __init__(self):
        super().__init__()
        self.fileName = ["Editor de texto", ".txt"]
        self.initUI()

    def initUI(self):

        # Sección de seleccionar carpeta
        folderSectionTitle = QLabel("Carpeta")
        self.fileFolder = QLineEdit()  # Línea donde está la carpeta
        self.fileFolder.setReadOnly(True)  # Hacemos que solo muestre el path y no podamos escribir en ella
        self.selectButton = QPushButton("Seleccionar")  # Botón de la sección

        # Sección de listado de directorios y archivos
        filesSectionTitle = QLabel("Archivos")  # Título de la sección
        self.fileTree = QTreeView()  # Crea una vista en forma de árbol
        self.fileSystemModel = QFileSystemModel(self.fileTree)  # Construye un modelo de los archivos del sistema
        self.fileSystemModel.setReadOnly(True)  # Hacemos que solo sea de modo lectura
        modelRoot = self.fileSystemModel.setRootPath("/home")  # /home será el directorio que se mostrará por defecto cuando iniciemos la app
        self.fileTree.setModel(self.fileSystemModel)  # Seteamos el modelo que creamos como modelo de nuestra vista en forma de árbol
        self.fileTree.setRootIndex(modelRoot)  # Seteamos el directorio por defecto que establecimos anteriormente (/home)
        self.fileTree.hideColumn(1)  # Escondemos el tamaño
        self.fileTree.hideColumn(2)  # Escondemos el tipo de archivo
        self.fileTree.hideColumn(3)  # Escondemos la fecha de modificación del archivo
        self.fileTree.setHeaderHidden(True)  # Escondemos la cabecera de la sección

        # Sección de texto
        self.textEdit = QTextEdit()  # Cuadro de texto donde podremos escribir para modificar y guardar archivos

        # Sección de botones
        self.saveButton = QPushButton("Guardar")  # Botón de guardar
        self.saveAsButton = QPushButton("Guardar como")  # Botón de guardar como

        # Creamos un diseño horizontal donde añadiremos los componentes de la sección de carpeta
        hbox = QHBoxLayout()
        hbox.addWidget(folderSectionTitle)
        hbox.addWidget(self.fileFolder)
        hbox.addWidget(self.selectButton)

        # Creamos un diseño vertical donde añadimos el horizontal que hemos creado previamente
        vbox = QVBoxLayout()
        vbox.setSpacing(30)
        vbox.addLayout(hbox)

        # Creamos una cuadrícula donde añadiremos los componentes de la sección de archivo especificando sus coordenadas
        grid = QGridLayout()
        grid.setSpacing(10)
        grid.addWidget(filesSectionTitle, 0, 0)
        grid.addWidget(self.fileTree, 1, 0, 1, 3)
        grid.addWidget(self.textEdit, 1, 3, 1, 5)
        # Añadimos el diseño de cuadricula de archivos al diseño vertical
        vbox.addLayout(grid)

        # Creamos un diseño horizontal donde añadiremos los componentes de la sección de botones
        # Añadimos margen después de los botones para que estén pegados a la esquina inferior izquierda
        self.buttomsLayout = QHBoxLayout()
        self.buttomsLayout.addWidget(self.saveButton)
        self.buttomsLayout.addWidget(self.saveAsButton)
        self.buttomsLayout.addStretch()
        # Añadimos el diseño de botones al diseño vertical
        vbox.addLayout(self.buttomsLayout)

        self.setLayout(vbox)  # Establecemos el diseño vertical como diseño principal
        self.setWindowTitle("Editor de texto")  # Título de la ventana
        self.setGeometry(300, 150, 1000, 700)  # Establecemos el tamaño y posicionamiento de la ventana
        self.show()  # Mostramos la ventana

        # Conectamos los botones a diferentes métodos
        self.selectButton.clicked.connect(self.openFolders)  # Dispara el método de abrir carpeta
        self.fileTree.doubleClicked.connect(self.doubleClickedTreeView)  # Dispara el método de desplegar carpeta en la sección de archivos
        self.saveButton.clicked.connect(self.saveFiles)  # Dispara el método de guardar archivo
        self.saveAsButton.clicked.connect(self.saveAsFiles)  # Dispara el método de guardar como

    def openFolders(self):  # Método de abrir carpeta
        directory = controller.openFolder(self)  # Dispara el método de seleccionar carpeta, el cual abre una ventana emergente
        modelRoot = self.fileSystemModel.setRootPath(directory)  # Establece la raiz el árbol en la carpeta seleccionada
        self.fileTree.setRootIndex(modelRoot)  # Muestra esta carpeta en la sección de archivos
        self.fileFolder.setText(directory)  # Muestra el path de la carpeta en la sección de carpeta

    def doubleClickedTreeView(self, index):  # Método de desplegar carpeta
        filedata = controller.doubleClickedTreeView(self, index)  # Dispara el método de doble click en la sección de archivos
        self.textEdit.setText(filedata)  # Muestra el contenido en el cuadro de texto

    def saveFiles(self):  # Método de guardar archivo
        controller.saveFile(self)  # Dispara el método de guardar archivo

    def saveAsFiles(self):  # Método de guardar como
        controller.saveAsFile(self)  # Dispara el método de guardar como

    def closeEvent(self, event):  # Método que se despliega cuando se intenta cerrar la app
        reply = QMessageBox.question(self, "Confirmación", "¿Deseas cerrar la app?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()  # Cerramos la app
        else:
            event.ignore()  # No cerramos la app (ignoramos la señal de cerrar)


if __name__ == "__main__":
    app = QApplication(sys.argv)  # Crea la app
    form = EditorTextosDlg()  # Crea un formulario
    sys.exit(app.exec_())  # Se inicia la app y se esperan eventos

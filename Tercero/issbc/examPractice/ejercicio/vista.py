import sys
from PyQt5.QtWidgets import QWidget, QPushButton, QApplication, QLabel, QGridLayout, QTextEdit, QLineEdit, QListWidget, QHBoxLayout, QVBoxLayout, QMessageBox

import controlador as controller


class Editor(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        self.filePath = None

        grid = QGridLayout()
        grid.setSpacing(10)

        # Diferentes tipos de inputs que tendrá la aplicacion
        self.labelLado = QLabel("Lado:", self)
        self.ladoEdit = QLineEdit()
        self.labelBase = QLabel("Base:", self)
        self.baseEdit = QLineEdit()
        self.labelAltura = QLabel("Altura:", self)
        self.alturaEdit = QLineEdit()
        self.labelRadio = QLabel("Radio:", self)
        self.radioEdit = QLineEdit()
        self.labelLado.hide()
        self.labelBase.hide()
        self.labelAltura.hide()
        self.labelRadio.hide()

        # Lista de tipos de figuras que se contemplan
        self.tiposFigura = QListWidget()
        self.tiposFigura.addItem("Cuadrado")
        self.tiposFigura.addItem("Rectángulo")
        self.tiposFigura.addItem("Triángulo")
        self.tiposFigura.addItem("Círculo")
        self.tiposFigura.itemDoubleClicked.connect(self.mostrarParametros)

        # Lista de figuras que podemos insertar con el botón de Añadir figura
        self.figuras = QListWidget()

        # Botones
        # Calcula el área de la figura cuyos parametros acabamos de introducir
        self.calcularAreaButton = QPushButton("Calcular Área")
        # Calcula el perímetro de la figura cuyos parametros acabamos de introducir
        self.calcularPerimetroButton = QPushButton("Calcular Perímetro")
        # Ordena de mayor a menos área las figuras introducidas
        self.ordenarMayorAreaButton = QPushButton("Ordenar Mayor Área")
        # Añadimos la figura a la lista de figuras con los parámetros introducidos
        self.addFiguraButton = QPushButton("Añadir figura")

        # Mostramos los botones
        self.buttomsLayout = QHBoxLayout()
        self.buttomsLayout.addStretch()
        self.buttomsLayout.addWidget(self.calcularAreaButton)
        self.buttomsLayout.addWidget(self.calcularPerimetroButton)
        self.buttomsLayout.addWidget(self.ordenarMayorAreaButton)
        self.buttomsLayout.addWidget(self.addFiguraButton)
        self.buttomsLayout.addStretch()

        # Mostramos las listas (de tipos de figuras y de figuras)
        self.grid = QGridLayout()
        self.grid.setSpacing(5)
        self.grid.addWidget(self.tiposFigura, 4, 1, 2, 1)
        self.grid.addWidget(self.figuras, 7, 1, 3, 1)
        mainLayout = QVBoxLayout()
        mainLayout.addLayout(self.grid)
        mainLayout.addLayout(self.buttomsLayout)

        self.setLayout(mainLayout)
        self.setGeometry(600, 300, 600, 600)
        self.setWindowTitle("Aplicacion de figuras")
        self.show()

        # Vinculamos una función a cada boton
        self.addFiguraButton.clicked.connect(self.addFiguraLista)
        self.calcularAreaButton.clicked.connect(self.calcularArea)
        self.calcularPerimetroButton.clicked.connect(self.calcularPerimetro)
        self.ordenarMayorAreaButton.clicked.connect(self.ordenarMayorArea)

        # En esta variable guardamos el tipo de figura seleccionada, para saber cual es y así poder calcular su area o permitro adecuadamente
        self.item = ""

    # Obtiene los parametros de la figura y se los manda a la funcion de calcular area
    def calcularArea(self):
        base, altura, lado, radio = self.getDatos()
        area = controller.calcularArea(base, altura, lado, radio, self)
        reply = QMessageBox.information(self, "Info", f"El area es {area}")

    # Obtiene los parametros de la figura y se los manda a la funcion de calcular perimetro
    def calcularPerimetro(self):
        base, altura, lado, radio = self.getDatos()
        perimetro = controller.calcularPerimetro(base, altura, lado, radio, self)
        reply = QMessageBox.information(self, "Info", f"El perímetro es {perimetro}")

    # Ordena de mayor a menor las figuras segun su area
    def ordenarMayorArea(self):
        base, altura, lado, radio = self.getDatos()
        controller.ordenarMayorArea(base, altura, lado, radio, self)

    # Obtiene los datos de los campos de texto
    def getDatos(self):
        base = self.baseEdit.text()
        altura = self.alturaEdit.text()
        lado = self.ladoEdit.text()
        radio = self.radioEdit.text()
        return base, altura, lado, radio

    # Pasa los parametros de las figuras a una funcion que las añade a la lista
    def addFiguraLista(self):
        base, altura, lado, radio = self.getDatos()
        controller.addFiguraLista(base, altura, lado, radio, self)

    # Muestra segun la figura que hayamos seleccionado los campos apropiados para que puedan ser introducidos
    def mostrarParametros(self, item):
        if item.text() == "Cuadrado":
            self.item = "Cuadrado"
            self.labelRadio.hide()
            self.labelBase.hide()
            self.labelAltura.hide()
            self.radioEdit.hide()
            self.baseEdit.hide()
            self.alturaEdit.hide()
            self.labelLado.show()
            self.grid.addWidget(self.labelLado, 0, 0)
            self.grid.addWidget(self.ladoEdit, 0, 1)
            self.ladoEdit.show()

        if item.text() == "Rectángulo":
            self.item = "Rectángulo"
            self.labelRadio.hide()
            self.labelLado.hide()
            self.radioEdit.hide()
            self.ladoEdit.hide()

            self.labelBase.show()
            self.labelAltura.show()
            self.grid.addWidget(self.labelBase, 0, 0)
            self.grid.addWidget(self.baseEdit, 0, 1)
            self.grid.addWidget(self.labelAltura, 1, 0)
            self.grid.addWidget(self.alturaEdit, 1, 1)
            self.baseEdit.show()
            self.alturaEdit.show()

        if item.text() == "Triángulo":
            self.item = "Triángulo"
            self.labelRadio.hide()
            self.labelLado.hide()
            self.radioEdit.hide()
            self.ladoEdit.hide()

            self.labelBase.show()
            self.labelAltura.show()
            self.grid.addWidget(self.labelBase, 0, 0)
            self.grid.addWidget(self.baseEdit, 0, 1)
            self.grid.addWidget(self.labelAltura, 1, 0)
            self.grid.addWidget(self.alturaEdit, 1, 1)
            self.baseEdit.show()
            self.alturaEdit.show()

        if item.text() == "Círculo":
            self.item = "Círculo"
            self.labelLado.hide()
            self.labelBase.hide()
            self.labelAltura.hide()
            self.ladoEdit.hide()
            self.baseEdit.hide()
            self.alturaEdit.hide()
            self.labelRadio.show()
            self.grid.addWidget(self.labelRadio, 0, 0)
            self.grid.addWidget(self.radioEdit, 0, 1)
            self.radioEdit.show()


def main():
    app = QApplication(sys.argv)
    ex = Editor()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

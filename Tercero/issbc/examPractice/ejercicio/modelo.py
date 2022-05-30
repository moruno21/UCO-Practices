from signal import alarm
from PyQt5.QtWidgets import QFileDialog, QTreeView, QListView, QFileSystemModel
from PyQt5.QtCore import QDir
from pathlib import Path

# Segun el tipo de figura hayamos el area de distinta forma
def calcularArea(base, altura, lado, radio, self):
    if self.item == "Cuadrado":
        return float(lado) * float(lado)

    if self.item == "Rectángulo":
        return float(base) * float(altura)

    if self.item == "Triángulo":
        return (float(base) * float(altura)) / 2

    if self.item == "Círculo":
        return 3.14 * float(radio) * float(radio)


# Segun el tipo de figura hayamos el perimetro de distinta forma
def calcularPerimetro(base, altura, lado, radio, self):
    if self.item == "Cuadrado":
        return float(lado) * 4

    if self.item == "Rectángulo":
        return (float(base) * 2) + (float(altura) * 2)

    if self.item == "Triángulo":
        return float(base) * 3

    if self.item == "Círculo":
        return 3.14 * 2 * float(radio)


# Ordena de mayor a menor
def ordenarMayorArea(base, altura, lado, radio, self):
    print("Ordenar mayor area")


# Añade una figura con sus parametros a la lista de figuras
def addFiguraLista(base, altura, lado, radio, self):
    if self.item == "Cuadrado":
        self.figuras.addItem("Cuadrado")
        self.figuras.addItem(f"Lado: {lado}")
        self.figuras.addItem("")

    if self.item == "Rectángulo":
        self.figuras.addItem("Rectángulo")
        self.figuras.addItem(f"Base: {base}")
        self.figuras.addItem(f"Altura: {altura}")
        self.figuras.addItem("")

    if self.item == "Triángulo":
        self.figuras.addItem("Triángulo")
        self.figuras.addItem(f"Base: {base}")
        self.figuras.addItem(f"Altura: {altura}")
        self.figuras.addItem("")

    if self.item == "Círculo":
        self.figuras.addItem("Círculo")
        self.figuras.addItem(f"Radio: {radio}")
        self.figuras.addItem("")

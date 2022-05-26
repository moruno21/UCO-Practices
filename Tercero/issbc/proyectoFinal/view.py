import sys
import controller as controller
from PyQt5.QtWidgets import *


class Planificador(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

        # Cargamos las opciones del dominio. Si este cambia, se vuelven a cargar
        self.loadDomain(self.comboDomain.currentText())
        self.comboDomain.currentTextChanged.connect(self.loadDomain)

    def initUI(self):

        # Titulos de secciones
        appTitle = QLabel("Bienvenido al planificador")
        appSubtitle = QLabel("Seleccione el dominio y comience con su planificación")
        originSectionTitle = QLabel("Origen")
        endSectionTitle = QLabel("Destino")
        explicationTitle = QLabel("Explicación")
        selectNumberTitle = QLabel("Recorridos a generar")
        topPathsTitle = QLabel("Top 5 mejores recorridos")

        # Listas de origenes y destinos
        self.originList = QListWidget()
        self.endList = QListWidget()

        # Seleccionar numero de recorridos
        self.numberOfPaths = QSpinBox()
        self.numberOfPaths.setMinimum(50)
        self.numberOfPaths.setMaximum(10000)

        # Listas de explicacion y top recorridos
        self.explanationList = QListWidget()
        self.topPathsList = QListWidget()

        # Botones
        self.planningButton = QPushButton("Planificar")  # Botón de planificar
        self.planningButton.setToolTip("Comenzar con la planificacion")
        self.planningButton.clicked.connect(self.planning)

        self.initializeButton = QPushButton("Limpiar")  # Botón de limpiar
        self.initializeButton.setToolTip("Limpiar las ventanas de explicacion y top recorridos")
        self.initializeButton.clicked.connect(self.explanationList.clear)
        self.initializeButton.clicked.connect(self.topPathsList.clear)

        self.exitButton = QPushButton("Salir")  # Botón de salir
        self.exitButton.setToolTip("Salir del planificador")
        self.exitButton.clicked.connect(self.close)

        # Creamos el combo para elegir el dominio
        self.comboDomain = QComboBox()
        self.comboDomain.addItem("Plan de Estadios")
        self.comboDomain.addItem("Plan de Excursion")

        # Creamos un diseño vertical donde añadimos el horizontal que hemos creado previamente
        vbox = QVBoxLayout()
        vbox.setSpacing(30)
        vbox.addWidget(appTitle)
        vbox.addWidget(appSubtitle)
        vbox.addWidget(self.comboDomain)

        # Creamos una cuadrícula donde añadiremos los componentes de la seccion de archivo especificando sus coordenadas
        grid = QGridLayout()
        grid.setSpacing(10)

        grid.addWidget(originSectionTitle, 0, 0, 1, 1)
        grid.addWidget(self.originList, 1, 0, 1, 1)

        grid.addWidget(endSectionTitle, 0, 2, 1, 1)
        grid.addWidget(self.endList, 1, 2, 1, 1)

        grid.addWidget(selectNumberTitle, 3, 0, 1, 3)
        grid.addWidget(self.numberOfPaths, 4, 0, 1, 3)

        grid.addWidget(self.planningButton, 5, 0, 1, 3)
        grid.addWidget(self.initializeButton, 6, 0, 1, 3)
        grid.addWidget(self.exitButton, 7, 0, 1, 3)

        grid.addWidget(explicationTitle, 0, 3, 1, 1)
        grid.addWidget(self.explanationList, 1, 3, 1, 50)

        grid.addWidget(topPathsTitle, 3, 3, 1, 1)
        grid.addWidget(self.topPathsList, 4, 3, 20, 50)

        # Añadir el diseño de cuadricula de archivos al diseño vertical
        vbox.addLayout(grid)

        self.setLayout(vbox)  # Diseño vertical como diseño principal
        self.setWindowTitle("Planificador")  # Título de la ventana
        self.setGeometry(300, 150, 1300, 700)  # Posicionamiento y tamaño de la ventana
        self.show()  # Mostramos la ventana

    # Carga el dominio que hayamos seleccionado en las lista de origen y destino
    def loadDomain(self, domain):

        self.originList.clear()  # Limpiamos la lista de origenes
        self.endList.clear()  # Limpiamos la lista de destinos

        # Segun el dominio que hayamos seleccionado, cargamos sus origenes y destinos
        if domain == "Plan de Excursion":
            for x in controller.EXCURSIONORIGIN.keys():
                self.originList.addItem(x)
            for x in controller.EXCURSIONEND.keys():
                self.endList.addItem(x)
        else:
            for x in controller.ESTADIOSORIGIN.keys():
                self.originList.addItem(x)
            for x in controller.ESTADIOSEND.keys():
                self.endList.addItem(x)

        self.originList.setCurrentRow(0)
        self.endList.setCurrentRow(0)

    # Método que se despliega cuando se intenta cerrar la app
    def closeEvent(self, event):
        reply = QMessageBox.question(self, "Confirmación", "¿Deseas cerrar el planificador?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

    # Planificar los recorridos
    def planning(self):
        if self.originList.currentItem().text() == self.endList.currentItem().text():  # Si seleccionamos un recorrido con origen y destino igual, salta el error
            msgBox = QMessageBox(QMessageBox.Critical, "Error", "El origen y el destino no pueden coincidir", QMessageBox.Close)
            msgBox.exec_()
        else:
            restrictions = {}
            self.explanationList.clear

            # Dependiendo del dominio, establecemos los nodos
            if self.comboDomain.currentText() == "Plan de Excursion":
                for x in controller.EXCURSIONORIGIN.keys():
                    if str(x) == self.originList.currentItem().text():
                        restrictions["origin"] = controller.EXCURSIONORIGIN[x]
                for x in controller.EXCURSIONEND.keys():
                    if str(x) == self.endList.currentItem().text():
                        restrictions["end"] = controller.EXCURSIONEND[x]
            else:
                for x in controller.ESTADIOSORIGIN.keys():
                    if str(x) == self.originList.currentItem().text():
                        restrictions["origin"] = controller.ESTADIOSORIGIN[x]
                for x in controller.ESTADIOSEND.keys():
                    if str(x) == self.endList.currentItem().text():
                        restrictions["end"] = controller.ESTADIOSEND[x]

            population = self.numberOfPaths.value()  # Obtenemos el numero de recorridos a generar
            planning, explanation = controller.PlanningEvent(self.comboDomain.currentText(), restrictions, population)  # Planificamos el evento
            self.explanationList.addItem(explanation)  # Añadimos la explicación al cuadro de explicación
            planings = ""
            for x in planning:
                planings += str(x) + "\n"
            self.topPathsList.addItem(planings)  # Añadimos los mejores recorridos a la secciono de top 5


if __name__ == "__main__":
    app = QApplication(sys.argv)  # Crea la app
    plan = Planificador()  # Crea el planificador
    sys.exit(app.exec_())  # Se inicia la app y se esperan eventos

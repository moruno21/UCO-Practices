from select import select
import sys
import p3.examPractice.table.controller as ctrl

from PyQt5.QtWidgets import QWidget, QTreeView, QFileSystemModel, QApplication, QLabel, QLineEdit, QTextEdit, QVBoxLayout, QHBoxLayout, QPushButton, QGridLayout, QTableWidget, QTableWidgetItem


class TableEditorDlg(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        self.title = QLabel("Carpeta")
        self.titleEdit = QLineEdit()
        self.openFileButton = QPushButton("Abrir")

        self.files = QLabel("Archivos")

        self.tableWidget = QTableWidget()

        # set row count
        self.tableWidget.setRowCount(30)

        # set column count
        self.tableWidget.setColumnCount(5)

        self.tableWidget.setItem(0, 0, QTableWidgetItem("Nombre"))
        self.tableWidget.setItem(0, 1, QTableWidgetItem("Apellidos"))
        self.tableWidget.setItem(0, 2, QTableWidgetItem("Calificación"))

        self.passedButton = QPushButton("Ver aprobados")
        self.saveAsButton = QPushButton("Guardar como")
        self.passedCountButton = QPushButton("Número de aprobados")
        self.meanButton = QPushButton("Media de calificaciónes")

        mainVbox = QVBoxLayout()
        mainVbox.setSpacing(20)

        folderHbox = QHBoxLayout()

        folderHbox.addWidget(self.title)
        folderHbox.addWidget(self.titleEdit)
        folderHbox.addWidget(self.openFileButton)

        mainVbox.addLayout(folderHbox)

        grid = QGridLayout()
        grid.setSpacing(10)

        """
        Aquí reamos un diseño de cuadrícula y establecemos
        el espacio entre los distintos elementos
        """

        grid.addWidget(self.files, 0, 0)

        grid.addWidget(self.tableWidget, 1, 0, 1, 4)

        grid.addWidget(self.passedButton, 2, 0)
        grid.addWidget(self.saveAsButton, 2, 1)
        grid.addWidget(self.passedCountButton, 2, 2)
        grid.addWidget(self.meanButton, 2, 3)

        mainVbox.addLayout(grid)

        self.setLayout(mainVbox)

        self.setGeometry(500, 500, 550, 500)
        self.setWindowTitle("Review")
        self.show()

        self.openFileButton.clicked.connect(self.openFile)
        self.passedButton.clicked.connect(self.listPassed)
        self.saveAsButton.clicked.connect(self.saveAs)
        self.passedCountButton.clicked.connect(self.calculatePassed)
        self.meanButton.clicked.connect(self.calculateMean)

    def openFile(self):
        ctrl.eventOpenFile(self)

    def listPassed(self):
        ctrl.eventListPassed(self)

    def saveAs(self):
        ctrl.eventSaveAs(self)

    def calculatePassed(self):
        ctrl.eventCalculatePassed(self)

    def calculateMean(self):
        # ctrl.eventCalculateMean(self)
        print(str(self.tableWidget.item(1, 1)))
        print(self.tableWidget.horizontalHeaderItem(2))
        print(self.tableWidget.horizontalHeaderItem(3))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = TableEditorDlg()
    sys.exit(app.exec_())

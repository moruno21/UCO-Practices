import sys
from PyQt5.QtWidgets import (
    QToolTip,
    QWidget,
    QDesktopWidget,
    QApplication,
    QMessageBox,
    QPushButton,
)
from PyQt5.QtGui import QFont


class Example(QWidget):  # Hereda de QWidget
    def __init__(self):  # Constructor
        super().__init__()  # Constructor de la clase padre
        self.initUI()  # Delegamos la creacion de la GUI a este método

    def initUI(self):
        QToolTip.setFont(QFont("SansSerif", 10))  # Establecemos la fuente para los tooltips
        self.setToolTip("Púlsame para cerrar la aplicación")  # Creamos el tooltip
        qbtn = QPushButton("Quit", self)  # #Creamos un botón
        qbtn.setToolTip("Cerrar aplicación")  # Asignamos un tooltip al boton
        qbtn.clicked.connect(QApplication.instance().quit)  # Cuando se emita el evento click, se dispara el slot quit
        qbtn.resize(qbtn.sizeHint())  # Establecemos el tamaño del boton. sizeHint() devuelve un tamaño recomendado para el boton
        qbtn.move(50, 50)  # Mueve el botón con respecto a la pantalla

        self.resize(250, 150)  # Establecemos el tamaño de la ventana
        self.center()  # Centramos la ventana
        self.setWindowTitle("Aplicación de ejemplo")  # Titulo de la ventana
        self.show()  # Muestra el widget en pantalla

    def center(self):  # Centramos la ventana
        qr = self.frameGeometry()  # Devuelve en forma de rectángulo la geometría de la pantalla, que se utilizará para centrar en ella la ventana
        cp = QDesktopWidget().availableGeometry().center()  # Calcula la resolución del monitor, y obtiene el punto central de este
        qr.moveCenter(cp)  # Establece el centro de la pantalla como  centro del rectángulo obtenido previamente
        self.move(qr.topLeft())  # Mueve la esquina superior izquierda de la aplicación a la esquina superior izquierda del rectángulo (el cuál ha sido centrado con el método anterior)

    def closeEvent(self, event):
        reply = QMessageBox.question(
            self,
            "Confirmación",
            "¿Desea cerrar?",
            QMessageBox.Yes | QMessageBox.No,
            QMessageBox.Yes,
        )  # Mensaje que se muesta en la caja al intentar cerrar
        if reply == QMessageBox.Yes:  # Aceptamos el evento (cerramos la aplicación)
            event.accept()
        else:  # No aceptamos el evento (no se cierra la aplicación)
            event.ignore()


def main():  # Creamos los objetos necesarios e iniciamos la aplicación
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()

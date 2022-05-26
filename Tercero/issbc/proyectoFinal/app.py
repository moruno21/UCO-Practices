import sys
from PyQt5.QtWidgets import QApplication
import view as view

app = QApplication(sys.argv)  # Crea la app
form = view.Planificador()  # Crea el planificador
sys.exit(app.exec_())  # Se inicia la app y se esperan eventos

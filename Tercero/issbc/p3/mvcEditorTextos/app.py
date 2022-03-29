# Archivo de aplicación de la p3 ISSBC

import sys
from PyQt5.QtWidgets import QApplication
import view as view

app = QApplication(sys.argv)  # Crea la app
form = view.EditorTextosDlg()  # Crea un formulario
sys.exit(app.exec_())  # Se inicia la app y se esperan eventos

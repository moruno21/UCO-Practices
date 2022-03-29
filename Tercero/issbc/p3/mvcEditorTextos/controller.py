# Controlador de la p3 ISSBC

import model as model


def doubleClickedTreeView(self, index):  # Retornamos lo que nos devuelva el método del modelo
    data = model.doubleClickedTreeView(self, index)
    return data


def openFolder(self):  # Retornamos lo que nos devuelva el método del modelo
    data = model.openFolder(self)
    return data


def saveFile(self):  # Retornamos lo que nos devuelva el método del modelo
    data = model.saveFile(self)
    return data


def saveAsFile(self):  # Retornamos lo que nos devuelva el método del modelo
    data = model.saveAsFile(self)
    return data

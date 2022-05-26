from bcPlanificacion import *

# Punto de la ciudad
class CordobaPlace(Node):
    def __init__(self, id, connections, type, name):
        Node.__init__(self, id, connections, type)
        self.name = name


# Grafo de los puntos de las ciudades
class ExcursionPlan(Graph):
    def __init__(self, name, id, nodes):
        Graph.__init__(self, nodes)
        self.id = id
        self.name = name
        self.nodes = nodes

    def __repr__(self):
        recorrido = str(self.nodes).strip("[]")  # Eliminamos los corchetes del array
        return "La " + str(self.name) + " dura " + str(self.getCost()) + " minutos: " + recorrido + "\n"


# Conjunto de puntos de la ciudad con sus distancias entre si.
cordobaPlaces = [
    CordobaPlace(0, [0, 28, 8, 12, 25, 24, 6, 9], "all", "Alcazar"),
    CordobaPlace(1, [28, 0, 24, 23, 32, 47, 19, 34], "all", "Estadio El Arcangel"),
    CordobaPlace(2, [8, 24, 0, 8, 17, 21, 4, 15], "all", "Mezquita Catedral"),
    CordobaPlace(3, [12, 23, 8, 0, 14, 30, 7, 20], "all", "Museo Bellas Artes"),
    CordobaPlace(4, [25, 32, 17, 14, 0, 30, 19, 32], "all", "Palacio de Viana"),
    CordobaPlace(5, [24, 47, 21, 30, 30, 0, 22, 22], "all", "Plaza de toros"),
    CordobaPlace(6, [6, 19, 4, 7, 19, 22, 0, 12], "all", "Puente Romano"),
    CordobaPlace(7, [9, 34, 15, 20, 32, 22, 12, 0], "all", "Zoologico"),
]

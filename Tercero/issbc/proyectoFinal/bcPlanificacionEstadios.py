from bcPlanificacion import *

# Nodeo de la red de estadios
class EstadioSpain(Node):
    def __init__(self, id, connections, type, name):
        Node.__init__(self, id, connections, type)
        self.name = name


# Grafo de los estadios
class EstadiosPlan(Graph):
    def __init__(self, name, id, nodes):
        Graph.__init__(self, nodes)
        self.name = name
        self.id = id
        self.nodes = nodes

    def __repr__(self):
        recorrido = str(self.nodes).strip("[]")  # Eliminamos los corchetes del array
        return "El " + str(self.name) + " recorre: " + str(self.getCost()) + " kilometros: " + recorrido + "\n"


# Conjunto de estadios con sus distancias entre si.
estadiosSpain = [
    EstadioSpain(0, [0, 610, 536, 392, 361, 13, 547, 592, 444, 309], "all", "Santiago Bernabeu"),
    EstadioSpain(1, [610, 0, 992, 602, 344, 602, 998, 1079, 560, 308], "all", "Camp Nou"),
    EstadioSpain(2, [536, 992, 0, 865, 656, 544, 5, 925, 901, 829], "all", "Ramon Sanchez Pijuan"),
    EstadioSpain(3, [392, 602, 865, 0, 611, 393, 866, 541, 101, 305], "all", "San Mamés"),
    EstadioSpain(4, [361, 344, 656, 611, 0, 355, 663, 953, 570, 305], "all", "Mestalla"),
    EstadioSpain(5, [13, 602, 544, 393, 355, 0, 545, 608, 449, 300], "all", "Wanda Metropolitano"),
    EstadioSpain(6, [547, 998, 5, 866, 663, 545, 0, 929, 920, 845], "all", "Benito Villamarín"),
    EstadioSpain(7, [592, 1079, 925, 541, 953, 608, 929, 0, 641, 783], "all", "Riazor"),
    EstadioSpain(8, [444, 560, 901, 101, 570, 449, 920, 641, 0, 263], "all", "Anoeta"),
    EstadioSpain(9, [309, 308, 829, 305, 305, 300, 845, 783, 263, 333], "all", "La Romareda"),
]

import random, copy
from bcPlanificacion import *
import bcPlanificacionEstadios as bcpestadios
import bcPlanificacionExcursion as bcpexcursion


class Planning:
    def __init__(self, restrictions, domain):
        self.domain = domain
        self.restrictions = restrictions
        self.solutions = []
        self.explanation = ""

        if self.domain == "Plan de Estadios":
            self.graph = bcpestadios.EstadiosPlan("first", 0, bcpestadios.estadiosSpain)
        elif self.domain == "Plan de Excursion":
            self.graph = bcpexcursion.ExcursionPlan("first", 0, bcpexcursion.cordobaPlaces)

    def getOrigins(self):
        return self.graph.getOrigins()

    def getEnds(self):
        return self.graph.getEnds()

    def getLastExplanation(self):
        return self.explanation

    # Genera el intercambio de nodos
    def execute(self, population):
        self.explanation = "Se generara un " + self.domain + " intercambiando nodos. En total se generaran " + str(population) + " recorridos\n"
        for i in range(0, population):
            self.explanation += "\t" + self.domain + " " + str(i) + " ha generado un intercambio de nodos\n"
            self.solutions.append(Ruta.execute(self.graph, self.restrictions, i))

        self.explanation += "Comprobando si la ruta es valida\n"
        validPaths = []
        for solution in self.solutions:
            self.explanation += "\tComprobando si la solucion con id " + str(solution.id) + " es valida\n"
            if Validation.execute(solution):
                self.explanation += "\t\tSolucion con id " + str(solution.id) + " valida!\n"
                validPaths.append(solution)
            else:
                self.explanation += "\t\tSolucion con id " + str(solution.id) + " invalida!\n"

        self.explanation += "Se mostraran los mejores cinco recorridos en el siguiente cuadro\n"
        return TopFivePaths.execute(validPaths), self.explanation


# Define los metodos que tendran las clases que la hereden
class Inferencia:
    def __init__(self):
        pass

    def execute(self):
        pass


# Comprobar la validez de un nodo
class Validation(Inferencia):
    def __init__(self):
        Inferencia.__init__(self)

    @staticmethod
    def execute(solution):
        return solution.isValid()


# Ordena los recorrido de menor a mayor coste
class SortByCost(Inferencia):
    def __init__(self):
        Inferencia.__init__(self)

    @staticmethod
    def execute(graph):
        graph.sort(key=lambda x: x.getCost(), reverse=False)
        return graph


# Obtner los 5 recorridos con menor coste
class TopFivePaths(Inferencia):
    def __init__(self):
        Inferencia.__init__(self)

    @staticmethod
    def execute(graphs):
        SortByCost.execute(graphs)
        return graphs[:5]


# Generar ruta (intercambio de nodos)
# Se establece el origen, el destino y se mezclan los nodos restantes
class Ruta(Inferencia):
    def __init__(self):
        Inferencia.__init__(self)

    @staticmethod
    def execute(solution, restrictions, id):

        finalSolution = copy.deepcopy(solution)
        auxSolution = copy.deepcopy(solution)

        finalSolution.setOrigin(auxSolution.getNodeById(restrictions["origin"]))
        finalSolution.setEnd(auxSolution.getNodeById(restrictions["end"]))

        finalSolution.id = id
        finalSolution.name = "Ruta " + str(id)

        auxSolution.removeById(restrictions["origin"])
        auxSolution.removeById(restrictions["end"])

        nodesToWork = auxSolution.nodes
        random.shuffle(nodesToWork)

        finalSolution.nodes[1 : (len(finalSolution.nodes) - 1)] = nodesToWork

        return finalSolution

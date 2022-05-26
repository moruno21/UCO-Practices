# Un nodo en el grafo
class Node:
    def __init__(self, id, connections, type):
        self.id = id
        self.connections = connections
        self.type = type

    # Obtiene el tipo de nodo
    def getType(self):
        self.type

    # Setea el tipo de nodo
    def setType(self, type):
        if type == "origin" or type == "end" or type == "middle" or type == "all":
            self.type = type

    def __repr__(self):
        return str(self.name)


# Conjunto de nodos
class Graph:
    def __init__(self, nodes):
        self.nodes = nodes

    # Obtiene un nodo del grafo por su id
    def getNodeById(self, id):
        for node in self.nodes:
            if node.id == id:
                return node

    # Borra un nodo del grafo por su id
    def removeById(self, id):
        for node in self.nodes:
            if node.id == id:
                self.nodes.remove(node)

    # Comprueba si el grafo es valido
    def isValid(self):
        infinity = float("inf")
        for i in range(len(self.nodes) - 1):
            if self.nodes[i].connections[self.nodes[i + 1].id] == infinity:
                return False
        return True

    # Establece el nodo inicial
    def setOrigin(self, node):
        self.nodes[0] = node

    # Establece el nodo final
    def setEnd(self, node):
        self.nodes[len(self.nodes) - 1] = node

    # Obtiene el origen de los nodos actuales
    def getOrigins(self):
        origins = []
        for node in self.nodes:
            if node.type == "origin" or node.type == "all":
                origins.append(node)
        return origins

    # Obtiene el fin de los nodos actuales
    def getEnds(self):
        ends = []
        for node in self.nodes:
            if node.type == "end" or node.type == "all":
                ends.append(node)
        return ends

    # Obtiene el coste del grafo
    def getCost(self):
        cost = 0
        for i in range(len(self.nodes) - 1):
            cost += self.nodes[i].connections[self.nodes[i + 1].id]
        return cost

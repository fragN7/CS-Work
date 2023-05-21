from main import myException
from random import choice
import copy


class UndirectedGraph:

    def __init__(self, vertices):
        self.__dictEdges = {}
        for i in range(0, vertices):
            self.__dictEdges[i] = []
        self.__E = []

    def addEdge(self, x, y):
        if x not in self.__dictEdges[y] and y not in self.__dictEdges[x]:
            self.__dictEdges[x].append(y)
            self.__dictEdges[y].append(x)
            self.__E.append((x, y))
            self.__E.append((y, x))
        else:
            raise myException("edge already exists")

    def addVertex(self, x):
        if x in self.__dictEdges:
            raise myException("vertex already exists")
        self.__dictEdges[x] = []

    def parseNeighbours(self, x):
        return self.__dictEdges[x]

    def parseKeys(self):
        return list(self.__dictEdges.keys())

    def getDegree(self, vertex):
        try:
            a = len(self.__dictEdges[vertex])
            b = 0
            for i in self.__dictEdges:
                if i != vertex and vertex in self.__dictEdges[i]:
                    b += 1
            return a + b
        except KeyError:
            raise myException("vertex doesn't exist")

    def getMaxDegreeVertex(self):
        max = -1
        vertex = -1
        for i in self.parseKeys():
            if self.getDegree(i) > max:
                max = self.getDegree(i)
                vertex = i
        return vertex

    def getCopy(self):
        new_graph = UndirectedGraph(len(self.__dictEdges))
        new_graph.__dictEdges = copy.deepcopy(self.__dictEdges)
        new_graph.__E = copy.deepcopy(self.__E)
        return new_graph

    def VertexCover(self):
        solution = set()
        new_graph = self.getCopy()
        while new_graph.__dictEdges != {}:
            v = new_graph.getMaxDegreeVertex()

            if new_graph.getDegree(v) == 0:
                break

            solution.add(v)
            del new_graph.__dictEdges[v]

            ok = True
            while ok:
                ok = False
                for x in new_graph.__dictEdges:
                    if v in new_graph.__dictEdges[x]:
                        new_graph.__dictEdges[x].remove(v)
                        ok = True
                        break
        return solution


    def printSubgraphs(self):
        for sg in self.__subgraphs:
            print(sg.parseKeys())

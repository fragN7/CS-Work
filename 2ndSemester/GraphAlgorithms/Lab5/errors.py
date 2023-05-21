from undirected import UndirectedGraph
from main import myException


class Console:

    def __init__(self):
        self.__fileName = "graph.txt"
        self.__options = {"load": self.__loadGraph,
                          "vertex cover": self.__vertexCover,
                          "add edge": self.__addEdge,
                          "add vertex": self.__addVertex
                          }

    def __printMenu(self):
        print("Hello: ")
        print("'load': load graph")
        print("'add edge': -add edge")
        print("'add vertex': -add vertex")
        print("'vertex cover': print the approximate vertex cover ")
        print("'exit': -to quit the program")

    def __loadGraph(self):
        try:
            with open(self.__fileName, "r") as file:
                firstLine = file.readline()
                firstLine = firstLine.strip().split()
                vertices, edges = int(firstLine[0]), int(firstLine[1])
                self.__graph = UndirectedGraph(vertices)
                for times in range(edges):
                    line = file.readline()
                    line = line.strip().split()
                    start, end, cost = int(line[0]), int(line[1]), int(line[2])
                    try:
                        self.__graph.addEdge(start, end)
                    except myException as me:
                        continue
            print("Graph loaded.")
        except IOError:
            raise myException("File Reading Error")

    def __vertexCover(self):
        print("The vertices forming the approximate minimum vertex cover are: ")
        print(self.__graph.VertexCover())

    def __addEdge(self):
        print("x:")
        x = int(input())
        print("y:")
        y = int(input())
        try:
            self.__graph.addEdge(x, y)
        except myException as me:
            print(me)

    def __addVertex(self):
        print("x:")
        x = int(input())
        try:
            self.__graph.addVertex(x)
        except myException as me:
            print(me)

    def main(self):
        while True:
            self.__printMenu()

            cmd = input("Enter your option here:\n")

            if cmd == "exit":
                return
            elif cmd in self.__options:
                self.__options[cmd]()


c = Console()
c.main()

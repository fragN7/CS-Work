from src.errors.exceptions import GraphException
from src.graph.set_graph import SetGraph
from src.graph.random_graph import RandomGraph


class UserInterface(object):

    def __init__(self, load_file_name, write_file_name):
        self.load_file_name = load_file_name
        self.write_file_name = write_file_name
        self.graph = SetGraph(0)
        self.commands = {
            "load": self.load_file,
            "write": self.write_file,

            "create graph": self.ui_create_graph,
            "vertices": self.ui_get_all_vertices,
            "print vertices": self.ui_print_all_vertices,
            "add vertex": self.ui_add_vertex,
            "remove vertex": self.ui_remove_vertex,
            "isolated vertices": self.ui_isolated_vertices,
            "shortest path": self.ui_shortest_path,
            "shortest reach": self.ui_shortest_reach,
            "highest reach": self.ui_highest_reach,
            "print degrees": self.ui_print_degrees,
            "inbound edges": self.ui_inbound_edges,
            "outbound edges": self.ui_outbound_edges,

            "edges": self.ui_print_edges,
            "is edge": self.ui_is_edge,
            "add edge": self.ui_add_edge,
            "remove edge": self.ui_remove_edge,
            "modify cost": self.ui_modify_cost,

            "copy graph": self.ui_copy_graph,
            "print graph": self.ui_print_graph,

            "random graph": self.ui_random_graph
        }

    def load_file(self):
        with open(self.load_file_name, "r") as file:
            first_line = file.readline()
            first_line = first_line.strip().split()
            vertices, edges = int(first_line[0]), int(first_line[1])
            self.graph = SetGraph(vertices)
            for i in range(edges):
                line = file.readline()
                line = line.strip().split()
                start, end, cost = int(line[0]), int(line[1]), int(line[2])
                self.graph.add_edge(start, end, cost)
        print("Graph loaded")

    def write_file(self):
        file = open(self.write_file_name, "w")
        for edge in self.graph.get_all_edges():
            file.write("{0} with cost {1}\n".format(edge, self.graph.get_cost(edge[0], edge[1])))
        print("Graph written")

    def ui_create_graph(self):
        vertices = int(input("Please enter a number of vertices:\n"))
        self.graph = SetGraph(vertices)

    def ui_get_all_vertices(self):
        print(self.graph.get_vertices())

    def ui_print_all_vertices(self):
        print(self.graph.get_vertices())

    def ui_add_vertex(self):
        vertex = int(input("Please enter a vertex number:\n"))
        self.graph.add_vertex(vertex)

    def ui_remove_vertex(self):
        vertex = int(input("Please enter a vertex number:\n"))
        self.graph.remove_vertex(vertex)

    def ui_isolated_vertices(self):
        print(self.graph.get_isolated_vertices())

    def ui_shortest_path(self):
        start_vertex = int(input("Please enter a starting vertex:"))
        end_vertex = int(input("Please enter a ending vertex:"))
        print(self.graph.shortest_path(start_vertex, end_vertex))

    def ui_shortest_reach(self):
        start_vertex = int(input("Please enter a starting vertex:"))
        end_vertex = int(input("Please enter a ending vertex:"))
        print(self.graph.shortest_reach(start_vertex, end_vertex))

    def ui_highest_reach(self):
        the_graph = self.graph.is_dag()
        if the_graph == 0:
            raise GraphException("Graph is not a DAG")
        else:
            print("Graph is a DAG graph")
            start_vertex = int(input("Please enter a starting vertex:"))
            end_vertex = int(input("Please enter a ending vertex:"))

            distance, previous = self.graph.highest_cost_path(start_vertex, end_vertex)

            path = []
            vertex = end_vertex
            path.append(vertex)
            while previous[vertex] != -1:
                path.append(previous[vertex])
                vertex = previous[vertex]

            path.reverse()
            print(path)
            print(distance)

    def ui_print_degrees(self):
        vertex = int(input("Please enter a vertex number: \n"))
        print("In degree: " + str(self.graph.get_degrees(vertex)[0]))
        print("Out degree: " + str(self.graph.get_degrees(vertex)[1]))

    def ui_inbound_edges(self):
        vertex = int(input("Please enter a vertex number: \n"))
        print(self.graph.inbound_dict[vertex])

    def ui_outbound_edges(self):
        vertex = int(input("Please enter a vertex number: \n"))
        print(self.graph.outbound_dict[vertex])

    def ui_print_edges(self):
        edges = self.graph.get_all_edges()
        for edge in edges:
            print(f"({edge[0]}, {edge[1]})")

    def ui_is_edge(self):
        start = int(input("Please enter a valid starting vertex:\n"))
        end = int(input("Please enter a valid ending vertex:\n"))
        if self.graph.is_edge(start, end):
            print(f"({start}, {end}) is an edge\n")
        else:
            print(f"({start}, {end}) is not an edge\n")

    def ui_add_edge(self):
        start = int(input("Please enter a valid starting vertex:\n"))
        end = int(input("Please enter a valid ending vertex:\n"))
        cost = int(input("Please enter the cost of the edge:\n"))
        self.graph.add_edge(start, end, cost)

    def ui_remove_edge(self):
        start = int(input("Please enter a valid starting vertex:\n"))
        end = int(input("Please enter a valid ending vertex:\n"))
        self.graph.remove_edge(start, end)

    def ui_modify_cost(self):
        start = int(input("Please enter a valid starting vertex:\n"))
        end = int(input("Please enter a valid ending vertex:\n"))
        new_cost = int(input("Please enter the new cost of the edge:\n"))
        self.graph.change_cost(start, end, new_cost)

    def ui_copy_graph(self):
        graph_copy = self.graph.copy_graph()
        if graph_copy:
            print("Made a copy of the graph stored as graph_copy.\n")

    def ui_print_graph(self):
        if self.graph.get_vertices():
            print(self.graph.get_vertices())
        for edge in self.graph.get_all_edges():
            print(f"{edge} with cost {self.graph.get_cost(edge[0], edge[1])}")

    @staticmethod
    def ui_random_graph():
        vertices = int(input("Please enter a number of vertices\n"))
        edges = int(input("Please enter a number of edges\n"))
        if vertices*vertices < edges:
            raise GraphException("Too many edges for a graph")
        random_graph = RandomGraph(vertices, edges)
        random_graph.print_random_graph()

    @staticmethod
    def print_menu():
        print("Welcome!!!\n")
        print("'load' - Load graph from file")
        print("'write' - Write current graph to file")
        print("'create graph' - Create a graph (Default has 0 vertices")
        print("--------------------------------------------------------------")
        print("'vertices' - Print the number of vertices")
        print("'print vertices' - Print all the vertices")
        print("'add vertex' - Add a vertex to the graph")
        print("'remove vertex' - Remove a vertex from the graph")
        print("'isolated vertices' - Print all the isolated vertices")
        print("'print degrees' - Print all the inbound and outbound degrees")
        print("'inbound edges' - Print the inbound edges of a vertex")
        print("'outbound edges' - Print the outbound edges of a vertex")
        print("--------------------------------------------------------------")
        print("'edges' - Print all the edges")
        print("'is edge' - Check if a edge is in the graph")
        print("'add edge' - Add an edge to the graph")
        print("'remove edge' - Remove an edge from the graph")
        print("'modify cost' - Change the cost of an edge")
        print("--------------------------------------------------------------")
        print("'copy graph' - Make a copy of the graph")
        print("'print graph' - Print the graph")
        print("'random graph' - Create a random graph")
        print("'shortest path' - Print the shortest path between two vertices")
        print("'highest reach' - Print the highest reach between two vertices")
        print("'shortest reach' - Print the shortest reach between two vertices")
        print("--------------------------------------------------------------")
        print("'exit' - Exit")

    def run(self):
        self.print_menu()
        while True:
            cmd = input("Please enter your option here:\n")
            if cmd == "exit":
                return
            elif cmd == "":
                continue
            elif cmd in self.commands:
                try:
                    self.commands[cmd]()
                except ValueError as ve:
                    print(ve)
                except GraphException as ge:
                    print(ge)
                except AttributeError:
                    print("No graph!")
                except IOError as ie:
                    print(ie)
                except KeyError:
                    continue
            else:
                print("Invalid command!")

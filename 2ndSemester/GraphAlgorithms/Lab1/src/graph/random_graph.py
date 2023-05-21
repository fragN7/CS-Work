import random
from src.errors.exceptions import GraphException
from src.graph.set_graph import SetGraph


class RandomGraph:

    def __init__(self, vertices, edges):
        self.graph = SetGraph(vertices)
        self.generate(vertices, edges)

    def generate(self, vertices, edges):
        list_of_vertices = [i for i in range(vertices)]
        costs = [0]
        for i in range(1, 101):
            costs.append(i)
            costs.append(-i)
        index = 0
        while index < edges:
            start = random.choice(list_of_vertices)
            end = random.choice(list_of_vertices)
            cost = random.choice(costs)
            try:
                self.graph.add_edge(start, end, cost)
                index = index + 1
            except GraphException:
                pass
        return self.graph

    def print_random_graph(self):
        for edge in self.graph.get_all_edges():
            print(f"{edge} with cost {self.graph.get_cost(edge[0], edge[1])}")

from src.errors.exceptions import GraphException
from queue import *
from heapq import *
import copy


class SetGraph:

    def __init__(self, vertices):
        self.inbound_dict = {}
        self.outbound_dict = {}
        self.cost_dict = {}
        for i in range(vertices):
            self.inbound_dict[i] = []
            self.outbound_dict[i] = []

    """
    Functions for EDGES
    """

    def get_all_edges(self):
        edges = []
        for edge in self.cost_dict:
            edges.append(edge)
        return edges[:]

    def is_edge(self, start_vertex, end_vertex):
        try:
            return end_vertex in self.outbound_dict[start_vertex]
        except KeyError:
            raise GraphException(f"({start_vertex}, {end_vertex}) is not an edge")

    def add_edge(self, start_vertex, end_vertex, cost_of_edge):
        err = ""
        if self.is_edge(start_vertex, end_vertex):
            err = err + "Already an edge"
        if len(err):
            raise GraphException(err)
        self.outbound_dict[start_vertex].append(end_vertex)
        self.inbound_dict[end_vertex].append(start_vertex)
        self.cost_dict[(start_vertex, end_vertex)] = cost_of_edge

    def remove_edge(self, start_vertex, end_vertex):
        if not self.is_edge(start_vertex, end_vertex):
            raise GraphException("Edge doesn't exist")
        del self.cost_dict[(start_vertex, end_vertex)]
        self.outbound_dict[start_vertex].remove(end_vertex)
        self.inbound_dict[end_vertex].remove(start_vertex)

    """
    Functions for COST
    """

    def get_cost(self, start_vertex, end_vertex):
        if self.is_edge(start_vertex, end_vertex):
            return self.cost_dict[(start_vertex, end_vertex)]

    def get_all_costs(self):
        costs = []
        for cost in self.cost_dict:
            costs.append(self.cost_dict[cost])
        return costs[:]

    def change_cost(self, start_vertex, end_vertex, new_cost):
        if not self.is_edge(start_vertex, end_vertex):
            raise GraphException("Edge doesn't exist")
        self.cost_dict[(start_vertex, end_vertex)] = new_cost

    """
    Functions for VERTICES
    """

    def get_vertices(self):
        return list(self.outbound_dict.keys())

    def get_number_of_vertices(self):
        return len(self.get_vertices())

    def get_isolated_vertices(self):
        vertices = []
        for vertex in self.get_vertices():
            if self.inbound_dict[vertex] == [] and self.outbound_dict[vertex] == []:
                vertices.append(vertex)
        return vertices[:]

    def get_degrees(self, vertex):
        try:
            return len(self.inbound_dict[vertex]), len(self.outbound_dict[vertex])
        except KeyError:
            GraphException("Vertex doesn't exist")

    def add_vertex(self, vertex):
        if vertex in self.get_vertices():
            raise GraphException("Vertex already exists")
        self.outbound_dict[vertex] = []
        self.inbound_dict[vertex] = []

    def remove_vertex(self, vertex):
        if vertex not in self.get_vertices():
            raise GraphException("Vertex doesn't exist")
        for i in self.outbound_dict[vertex]:
            self.inbound_dict[i].remove(vertex)
            del self.cost_dict[(vertex, i)]
        del self.outbound_dict[vertex]
        for i in self.inbound_dict[vertex]:
            self.outbound_dict[i].remove(vertex)
            del self.cost_dict[(i, vertex)]
        del self.inbound_dict[vertex]

    def vertex_iterator(self):
        vertices_number = self.get_number_of_vertices()
        for vertex in range(vertices_number):
            yield vertex

    def topological_sort(self):
        sorted_list = []
        q = Queue()
        count = {}

        for vertex in self.inbound_dict:
            count[vertex] = len(self.inbound_dict[vertex])
            if count[vertex] == 0:
                q.put(vertex)

        while not q.empty():
            current = q.get()
            sorted_list.append(current)

            for vertex in self.outbound_dict[current]:
                count[vertex] -= 1
                if count[vertex] == 0:
                    q.put(vertex)

        if len(sorted_list) < len(self.inbound_dict):
            sorted_list = []

        return sorted_list

    def is_dag(self):
        sorted_list = self.topological_sort()
        if not sorted_list:
            return False
        return True

    def highest_cost_path(self, start_vertex, end_vertex):
        sorted_list = self.topological_sort()
        distance = {}
        previous = {}
        inf = float('-inf')

        for vertex in sorted_list:
            distance[vertex] = inf
            previous[vertex] = -1

        distance[start_vertex] = 0

        for first_vertex in sorted_list:
            if first_vertex == end_vertex:
                break
            for second_vertex in self.outbound_dict[first_vertex]:
                if distance[second_vertex] < distance[first_vertex] + self.get_cost(first_vertex, second_vertex):
                    distance[second_vertex] = distance[first_vertex] + self.get_cost(first_vertex, second_vertex)
                    previous[second_vertex] = first_vertex

        return distance[end_vertex], previous

    def dijkstra(self, start, end=None):
        dist = dict()
        prev = dict()
        dist[start] = 0
        q = list()
        heappush(q, (dist[start], start))

        while q:
            distance, vertex = heappop(q)
            if vertex == end:
                break
            if distance == dist[vertex]:
                for neighbor in self.outbound_dict[vertex]:
                    if neighbor not in dist or dist[neighbor] > dist[vertex] + self.get_cost(vertex, neighbor):
                        dist[neighbor] = dist[vertex] + self.get_cost(vertex, neighbor)
                        prev[neighbor] = vertex
                        heappush(q, (dist[neighbor], neighbor))
        return dist, prev

    def shortest_reach(self, start_vertex, end_vertex):
        """

        :param start_vertex:
        :param end_vertex:
        :return:
        """

        if self.get_number_of_vertices() == 0:
            raise GraphException("No vertices in graph")

        dist, prev = self.dijkstra(start_vertex, end_vertex)

        path = list()
        y = end_vertex

        while y != start_vertex:
            path.append(y)
            y = prev[y]

        path.append(start_vertex)
        path.reverse()
        return path, dist[end_vertex]

    def shortest_path(self, start_vertex, end_vertex):
        """
        Performs a breadth-first search form the end vertex to the starting vertex, creates a queue in which
        all inbound edges are being added which are not visited, and also computing the parent
        :param start_vertex: Starting vertex
        :param end_vertex: Ending vertex
        :return:
        """

        if self.get_number_of_vertices() == 0:
            raise GraphException("No vertices in graph")

        if self.is_edge(start_vertex, end_vertex):
            return [start_vertex, end_vertex]

        visited = {}
        level = {}
        parent = {}
        queue = Queue()

        for vertex in range(self.get_number_of_vertices()):
            visited[vertex] = False
            parent[vertex] = None
            level[vertex] = -1

        visited[end_vertex] = True
        level[end_vertex] = 0
        queue.put(end_vertex)

        while not queue.empty():
            u = queue.get()
            visited[u] = True
            for neighbour in self.inbound_dict[u]:
                if not visited[neighbour]:
                    visited[neighbour] = True
                    parent[neighbour] = u
                    level[neighbour] = int(level[u]) + 1
                    queue.put(neighbour)

        path = []
        while start_vertex is not None:
            path.append(start_vertex)
            start_vertex = parent[start_vertex]

        return path[:]

    def copy_graph(self):
        new_graph = SetGraph(len(self.get_vertices()))
        new_graph.inbound_dict = copy.deepcopy(self.inbound_dict)
        new_graph.outbound_dict = copy.deepcopy(self.outbound_dict)
        new_graph.cost_dict = copy.deepcopy(self.cost_dict)
        return new_graph

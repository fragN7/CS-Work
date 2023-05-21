import unittest
from undirected import UndirectedGraph


class Testing(unittest.TestCase):

    def setUp(self):
        self.graph = UndirectedGraph(11)

    def testAll(self):
        self.graph.addEdge(1, 2)
        self.graph.addEdge(2, 3)
        self.graph.addEdge(3, 4)
        self.graph.addEdge(1, 5)
        self.graph.addEdge(0, 3)
        self.graph.addEdge(7, 8)
        self.graph.addEdge(8, 9)
        self.graph.addEdge(9, 10)

        print(self.graph.VertexCover())
        # print(self.graph.VertexCover())

        self.assertEqual(self.graph.VertexCover(), {1, 3, 8, 9})


if __name__ == '__main__':
    tests = Testing()
    tests.testAll()

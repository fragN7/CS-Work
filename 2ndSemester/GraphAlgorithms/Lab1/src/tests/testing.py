import unittest
from src.graph.set_graph import SetGraph
from src.graph.random_graph import RandomGraph


class Tests(unittest.TestCase):

    def setUp(self):
        self.random_graph = RandomGraph(5, 17)
        self.graph = SetGraph(7)

    def test_all(self):
        self.assertEqual(len(self.graph.get_vertices()), 7)
        self.assertEqual(self.graph.get_number_of_vertices(), 7)
        self.assertEqual(len(self.graph.get_isolated_vertices()), 7)

        self.graph.add_edge(1, 2, 4)
        self.graph.add_edge(2, 3, 15)
        self.graph.add_edge(3, 4, 3)
        self.graph.add_edge(1, 5, 80)

        self.assertEqual(self.graph.highest_cost_path(1, 4)[0], 22)

        self.graph.add_edge(3, 5, 13)
        self.graph.add_edge(1, 6, 9)
        self.graph.add_edge(6, 5, 40)

        self.assertEqual(self.graph.shortest_reach(1, 5)[1], 32)
        self.assertEqual(self.graph.shortest_path(1, 5), [1, 5])

        self.assertEqual(self.graph.get_degrees(1)[0], 0)
        self.assertEqual(self.graph.get_degrees(1)[1], 3)

        self.graph.add_vertex(7)

        self.assertFalse(self.graph.is_edge(2, 1))
        self.assertTrue(self.graph.is_edge(1, 2))
        self.assertTrue(len(self.graph.get_all_edges()), 4)
        self.assertTrue(len(self.graph.get_all_costs()), 4)
        self.graph.change_cost(2, 3, 13)
        self.graph.remove_vertex(1)

        self.graph.copy_graph()


if __name__ == '__main__':
    tests = Tests()
    tests.test_all()

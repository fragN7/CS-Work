import unittest
from src.board.Board import Board


class Tests(unittest.TestCase):

    def setUp(self):
        self.board = Board()

    def testNothing(self):
        self.assertFalse(self.board.get_game_review())

    def testRows(self):
        for i in range(6):
            self.board.update_board(i, 0, "X")
        self.assertTrue(self.board.get_game_review())

    def testColumns(self):
        for i in range(6):
            self.board.update_board(i, 0, "-")
        for i in range(6):
            self.board.update_board(0, i, "X")
        self.assertTrue(self.board.get_game_review())

    def testMainDiagonal(self):
        for i in range(6):
            self.board.update_board(0, i, "-")
        for i in range(6):
            self.board.update_board(i, i, "X")
        self.assertTrue(self.board.get_game_review())

    def testSecondaryDiagonal(self):
        for i in range(6):
            self.board.update_board(i, i, "-")
        self.board.update_board(0, 5, "X")
        self.board.update_board(1, 4, "X")
        self.board.update_board(2, 3, "X")
        self.board.update_board(3, 2, "X")
        self.board.update_board(4, 1, "X")
        self.assertTrue(self.board.get_game_review())


if __name__ == '__main__':
    test = Tests()
    test.testNothing()
    test.testRows()
    test.testColumns()
    test.testMainDiagonal()
    test.testSecondaryDiagonal()

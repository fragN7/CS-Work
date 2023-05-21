from src.board.Board import Board
from src.move.Move import Move
from src.validation.Validation import Validation
from src.errors.Exceptions import ValidError
import unittest


class Testing(unittest.TestCase):

    def setUp(self):
        self.board = Board()
        self.validation = Validation(self.board)
        self.move = Move(self.board, self.validation)

    def testBoard(self):

        x = 0
        y = 0
        turn = 'X'

        board = [['X', '-', '-'],
                 ['-', '-', '-'],
                 ['-', '-', '-']]

        self.board.update_board(x, y, turn)
        self.assertEqual(board, self.board.get_board())

        valid_locations = self.board.get_valid_locations()
        self.assertEqual(valid_locations, [[0, 1], [0, 2], [1, 0], [1, 1], [1, 2], [2, 0], [2, 1], [2, 2]])

        self.board.update_board(0, 0, 'X')
        self.board.update_board(0, 1, 'X')
        self.board.update_board(0, 2, 'X')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(0, 0, 'X')
        self.board.update_board(1, 0, 'X')
        self.board.update_board(2, 0, 'X')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(0, 0, 'X')
        self.board.update_board(1, 1, 'X')
        self.board.update_board(2, 2, 'X')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(2, 0, 'X')
        self.board.update_board(1, 1, 'X')
        self.board.update_board(0, 2, 'X')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(0, 0, 'O')
        self.board.update_board(0, 1, 'O')
        self.board.update_board(0, 2, 'O')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(0, 0, 'O')
        self.board.update_board(1, 0, 'O')
        self.board.update_board(2, 0, 'O')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(0, 0, 'O')
        self.board.update_board(1, 1, 'O')
        self.board.update_board(2, 2, 'O')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()

        self.board.update_board(2, 0, 'O')
        self.board.update_board(1, 1, 'O')
        self.board.update_board(0, 2, 'O')
        self.assertTrue(self.board.is_game_done())

        self.board.clear_board()
        self.assertFalse(self.board.is_game_done())

    def testValidation(self):
        x = 4
        y = 4
        try:
            with self.assertRaises(self.validation.validate_placing(x, y)) as ve:
                self.assertEqual(str(ve.exception), "4 and 4 are out of bounds")
        except ValidError:
            print('')

        self.board.clear_board()
        self.board.update_board(2, 0, 'O')
        self.board.update_board(1, 1, 'O')
        self.board.update_board(0, 2, 'O')

        x = 2
        y = 0
        try:
            with self.assertRaises(self.validation.validate_placing(x, y)) as ve:
                self.assertEqual(str(ve.exception), "2 and 0 is already occupied")
        except ValidError:
            print('')

        x = 4
        y = 4
        turn = 'O'
        try:
            with self.assertRaises(self.validation.validate_move(x, y, turn)) as ve:
                self.assertEqual(str(ve.exception), "4 and 4 are out of bounds")
        except ValidError:
            print('')

        x = 2
        y = 1

        try:
            with self.assertRaises(self.validation.validate_move(x, y, turn)) as ve:
                self.assertEqual(str(ve.exception), "2 and 1 are not occupied by 'O'")
        except ValidError:
            print('')

        x1 = 0
        y1 = 0

        x2 = 2
        y2 = 2

        try:
            with self.assertRaises(self.validation.validate_adjacency(x1, y1, x2, y2)) as ve:
                self.assertEqual(str(ve.exception), "The pieces selected are too far away")
        except ValidError:
            print('')

        x1 = 0
        y1 = 0

        x2 = 1
        y2 = 2

        try:
            with self.assertRaises(self.validation.validate_adjacency(x1, y1, x2, y2)) as ve:
                self.assertEqual(str(ve.exception), "The pieces selected are too far away")
        except ValidError:
            print('')

    def testMove(self):

        x = 0
        y = 0
        turn = 'X'
        self.board.clear_board()

        self.move.enter_move(x, y, turn)
        board = [['X', '-', '-'],
                 ['-', '-', '-'],
                 ['-', '-', '-']]
        self.assertEqual(board, self.board.get_board())
        x1 = 1
        y1 = 1
        self.move.move_move(x, y, x1, y1, turn)
        board = [['-', '-', '-'],
                 ['-', 'X', '-'],
                 ['-', '-', '-']]
        self.assertEqual(board, self.board.get_board())


if __name__ == '__main__':
    tests = Testing()
    tests.testBoard()
    tests.testValidation()
    tests.testMove()

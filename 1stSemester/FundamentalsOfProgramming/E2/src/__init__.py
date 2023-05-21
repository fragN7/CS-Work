from src.ui.UserInterface import UserInterface
from src.board.Board import Board
from src.move.Move import Move
from src.validation.Validation import Validation


if __name__ == '__main__':
    board = Board()
    valid = Validation(board)
    move = Move(board, valid)
    ui = UserInterface(move, board)
    ui.run()

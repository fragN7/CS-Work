from src.errors.Exceptions import ValidError


class Validation:

    def __init__(self, board):
        self.board = board

    def validate_placing(self, x, y):
        """
        :param x: x position
        :param y: y position
        This function raises errors if:
            1) x and y are not 0 or 1 or 2.
            2) at the position (x, y) is already a turn('X' or 'O').
        """
        place = [x, y]
        if x not in range(0, 3) or y not in range(0, 3):
            raise ValidError(f"{x} and {y} are out of bounds")
        valid_locations = self.board.get_valid_locations()
        if place not in valid_locations:
            raise ValidError(f"{x} and {y} is already occupied")

    def validate_move(self, x, y, turn):
        """
        :param x: x position
        :param y: y position
        :param turn: either 'X' or 'O'
        This function raises errors if:
            1) x and y are not 0 or 1 or 2.
            2) at the position (x, y) is not the turn(either 'X' or 'O').
        """
        if x not in range(0, 3) or y not in range(0, 3):
            raise ValidError(f"{x} and {y} are out of bounds")
        board = self.board.get_board()
        if board[x][y] != turn:
            raise ValidError(f"{x} and {y} are not occupied by {turn}")

    @staticmethod
    def validate_adjacency(x1, y1, x2, y2):
        """
        :param x1: x start position
        :param y1: y start position
        :param x2: x end position
        :param y2: y end position
        This function raises errors if the 2 positions (x1, y1) and (x2, y2) are not adjacent.
        """
        if abs(x2 - x1) > 1:
            raise ValidError("The pieces selected are too far away")
        if abs(y2 - y1) > 1:
            raise ValidError("The pieces selected are too far away")

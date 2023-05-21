class Move:

    def __init__(self, board, validation):
        self.board = board
        self.validation = validation

    def enter_move(self, x, y, turn):
        """
        :param x: x position
        :param y: y position
        :param turn: either 'X' or 'O'
            The function first calls the validator function which checks if it is a valid position, and if it doesn't
        raise any error, the function 'self.board.update_board(x, y, turn)' puts the turn in the position (x, y).
        """
        self.validation.validate_placing(x, y)
        self.board.update_board(x, y, turn)

    def move_move(self, x1, y1, x2, y2, turn):
        """
        :param x1: x start position
        :param y1: y start position
        :param x2: x end position
        :param y2: y end position
        :param turn: either 'X' or 'O'
            The first 3 functions validate the spot, the first one checks the starting position validity, the second
        function checks the ending position validity and the third function checks if in the movement phase, the moves
        are valid.
            The last two functions move the turn to it's correct position and put in the position before '-'.
        """
        self.validation.validate_move(x1, y1, turn)
        self.validation.validate_placing(x2, y2)
        self.validation.validate_adjacency(x1, y1, x2, y2)
        self.board.update_board(x1, y1, "-")
        self.board.update_board(x2, y2, turn)

    def best_move(self):
        turn = 'X'
        x = self.board.not_let_win(turn)[0]
        y = self.board.not_let_win(turn)[1]
        return x, y


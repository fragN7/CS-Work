import random


class Move:

    def __init__(self, board, validation):
        self.board = board
        self.validation = validation

    def move(self, x, y, value):
        self.validation.move_validation(x, y, value)
        self.board.update_board(x, y, value)

    def get_most_used_value(self):
        x_sum = 0
        o_sum = 0
        for i in range(6):
            for j in range(6):
                if self.board.get_board()[i][j] == "X":
                    x_sum += 1
                elif self.board.get_board()[i][j] == "O":
                    o_sum += 1
        if x_sum > o_sum:
            return "X"
        return "O"

    def get_winning_move(self):
        x_sum = 0
        o_sum = 0
        dash_sum = 0
        for i in range(6):
            for j in range(6):
                if self.board.get_board()[i][j] == "X":
                    x_sum += 1
                elif self.board.get_board()[i][j] == "O":
                    o_sum += 1
                else:
                    dash_sum += 1
            if x_sum >= 4 and dash_sum >= 1:
                for z in range(6):
                    if self.board.get_board()[i][z] == "-":
                        self.board.update_board(i, z, "X")
                        if not self.board.get_game_review():
                            self.board.update_board(i, z, "-")
                        else:
                            return
            if o_sum >= 4 and dash_sum >= 1:
                for z in range(6):
                    if self.board.get_board()[i][z] == "-":
                        self.board.update_board(i, z, "O")
                        if not self.board.get_game_review():
                            self.board.update_board(i, z, "-")
                        else:
                            return
        self.board.update_board(random.choice([0, 1, 2, 3, 4, 5]), random.choice([0, 1, 2, 3, 4, 5]), self.get_most_used_value())

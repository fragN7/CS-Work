from src.errors.Exceptions import ValidError
import random


class UserInterface:

    def __init__(self, board, move):
        self.board = board
        self.move = move

    def run(self):
        turn = "X"
        self.board.print_board()
        placement = 0
        choices = [0, 1, 2]
        while placement != 4:
            if turn == "X":
                try:
                    x = int(input("Player X, please select a valid row (0-2):\n"))
                    y = int(input("Player X, please select a valid column (0-2):\n"))
                    self.move.enter_move(x, y, turn)
                    self.board.print_board()
                    if self.board.is_game_done():
                        print("Congrats player X you have won!!!")
                        return
                    turn = "O"
                except ValueError:
                    print("Please select a integer")
                except ValidError as ve:
                    print(str(ve))
            else:
                try:
                    # x = random.choice(choices)
                    # y = random.choice(choices)
                    result = self.move.best_move()
                    x = result[0]
                    y = result[1]
                    self.move.enter_move(x, y, turn)
                    placement = placement + 1
                    self.board.print_board()
                    if self.board.is_game_done():
                        print("Congrats player O you have won!!!")
                        return
                    turn = "X"
                except ValidError:
                    t = 1
        """
        Placement phase ends.
        """
        while True:
            if turn == "X":
                try:
                    x1 = int(input("Player X, please select a valid row which has an X (0-2):\n"))
                    y1 = int(input("Player X, please select a valid column which has an X (0-2):\n"))

                    x2 = int(input("Player X, please select a valid row (0-2):\n"))
                    y2 = int(input("Player X, please select a valid column (0-2):\n"))

                    self.move.move_move(x1, y1, x2, y2, turn)
                    self.board.print_board()
                    if self.board.is_game_done():
                        print("Congrats player X you have won!!!")
                        return
                    turn = "O"
                except ValueError:
                    print("Please select a integer")
                except ValidError as ve:
                    print(str(ve))
            else:
                try:
                    x1 = random.choice(choices)
                    y1 = random.choice(choices)

                    x2 = random.choice(choices)
                    y2 = random.choice(choices)

                    self.move.move_move(x1, y1, x2, y2, turn)
                    placement = placement + 1
                    self.board.print_board()
                    if self.board.is_game_done():
                        print("Congrats player O you have won!!!")
                        return
                    turn = "X"
                except ValidError:
                    t = 1

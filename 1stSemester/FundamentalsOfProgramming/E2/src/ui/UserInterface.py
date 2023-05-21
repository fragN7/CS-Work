from src.errors.exceptions import ValidationError


class UserInterface:

    def __init__(self, move, board):
        self.move = move
        self.board = board

    def run(self):
        self.board.print_board()
        print("------------------------------")
        turn = 0
        while True:
            try:
                if turn == 0:
                    self.move.get_winning_move()
                    self.board.print_board()
                    if self.board.get_game_review():
                        print("Order won")
                        return
                    valid_locations = self.board.get_valid_locations()
                    if not valid_locations:
                        print("Chaos won")
                        return
                    print("------------------------------")
                    turn = 1
            except ValueError:
                x = 1
            except ValidationError:
                x = 1
            try:
                if turn == 1:
                    x = int(input("Please enter a valid row 1-6:\n")) - 1
                    y = int(input("Please enter a valid column 1-6:\n")) - 1
                    value = input("Please enter a valid entry X/O:\n").upper()
                    self.move.move(x, y, value)
                    self.board.print_board()
                    if self.board.get_game_review():
                        print("Order won")
                        return
                    valid_locations = self.board.get_valid_locations()
                    if not valid_locations:
                        print("Chaos won")
                        return
                    print("------------------------------")
                    turn = 0
            except ValueError:
                print("Please enter a number type")
            except ValidationError as ve:
                print(str(ve))

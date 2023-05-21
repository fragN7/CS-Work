import random


class Board:

    def __init__(self):
        self.board = [['-', '-', '-'],
                      ['-', '-', '-'],
                      ['-', '-', '-']]

    def update_board(self, x, y, turn):
        """
        :param x: x position
        :param y: y position
        :param turn: either 'X' or 'O'
        The function puts in the (x, y) position the turn.
        """
        self.board[x][y] = turn

    def get_valid_locations(self):
        """
        The function checks for the character '-' which is a valid position, and it appends it to a list.
        :return: List of valid locations
        """
        valid_locations = []
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == '-':
                    valid_locations.append([i, j])
        return valid_locations

    def is_game_done(self):
        """
        The function checks for horizontal, vertical and diagonal wins, for both turns('X' or 'O').
        :return: True if the game is won, False otherwise
        """
        if self.board[0][0] == self.board[0][1] == self.board[0][2] == "X":
            return True
        if self.board[1][0] == self.board[1][1] == self.board[1][2] == "X":
            return True
        if self.board[2][0] == self.board[2][1] == self.board[2][2] == "X":
            return True

        if self.board[0][0] == self.board[1][1] == self.board[2][2] == "X":
            return True
        if self.board[0][2] == self.board[1][1] == self.board[2][0] == "X":
            return True

        if self.board[0][0] == self.board[1][0] == self.board[2][0] == "X":
            return True
        if self.board[0][1] == self.board[1][1] == self.board[2][1] == "X":
            return True
        if self.board[0][2] == self.board[1][2] == self.board[2][2] == "X":
            return True

        if self.board[0][0] == self.board[0][1] == self.board[0][2] == "O":
            return True
        if self.board[1][0] == self.board[1][1] == self.board[1][2] == "O":
            return True
        if self.board[2][0] == self.board[2][1] == self.board[2][2] == "O":
            return True

        if self.board[0][0] == self.board[1][1] == self.board[2][2] == "O":
            return True
        if self.board[0][2] == self.board[1][1] == self.board[2][0] == "O":
            return True

        if self.board[0][0] == self.board[1][0] == self.board[2][0] == "O":
            return True
        if self.board[0][1] == self.board[1][1] == self.board[2][1] == "O":
            return True
        if self.board[0][2] == self.board[1][2] == self.board[2][2] == "O":
            return True

        return False

    def not_let_win(self, turn):
        choices = [0, 1, 2]

        """
        In this segment the function is checking if it is a possible win on horizontal lines.
        If there are two of the same kind, we return the vacant position.
        """

        s = 0
        for i in range(3):
            for j in range(3):
                if self.board[i][j] == turn:
                    s = s + 1
            if s == 2:
                for j in range(3):
                    if self.board[i][j] == '-':
                        return i, j

        """
        In this segment the function is checking if it is a possible win on vertical lines.
        If there are two of the same kind, we return the vacant position.
        """

        s1 = 0
        for j in range(3):
            for i in range(3):
                if self.board[i][j] == turn:
                    s1 = s1 + 1
            if s1 == 2:
                for i in range(3):
                    if self.board[i][j] == '-':
                        return i, j

        """
        In this segment the function is checking if it is a possible win on diagonal lines.
        If there are two of the same kind, we return the vacant position.
        """

        s3 = 0
        for i in range(3):
            if self.board[i][i] == turn:
                s3 = s3 + 1
        if s3 == 2:
            for i in range(3):
                if self.board[i][i] == '-':
                    return i, i

        s4 = 0
        i = 0
        j = 2
        while i <= 2 and j >= 0:
            if self.board[i][j] == turn:
                s4 = s4 + 1
            i = i + 1
            j = j - 1
        if s4 == 2:
            while i <= 2 and j >= 0:
                if self.board[i][j] == '-':
                    return i, j
                i = i + 1
                j = j - 1

        x = random.choice(choices)
        y = random.choice(choices)
        return x, y

    def print_board(self):
        for i in range(3):
            print(self.board[i])

    def clear_board(self):
        """
        Function to clear the board, used in tests.
        """
        for i in range(3):
            for j in range(3):
                self.board[i][j] = '-'

    def get_board(self):
        """
        :return: The board
        """
        return self.board[:]

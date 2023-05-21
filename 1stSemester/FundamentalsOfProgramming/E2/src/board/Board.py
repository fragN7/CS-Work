class Board:

    def __init__(self):
        self.board = [["-", "-", "-", "-", "-", "-"],
                      ["-", "-", "-", "-", "-", "-"],
                      ["-", "-", "-", "-", "-", "-"],
                      ["-", "-", "-", "-", "-", "-"],
                      ["-", "-", "-", "-", "-", "-"],
                      ["-", "-", "-", "-", "-", "-"]]

    def update_board(self, x, y, value):
        self.board[x][y] = value

    def get_valid_locations(self):
        valid_locations = []
        for i in range(6):
            for j in range(6):
                if self.board[i][j] == "-":
                    valid_locations.append([i, j])
        return valid_locations[:]

    def get_game_review(self):
        """
        This code fragment checks for wins on rows.
        There are only two possible ways of winning on rows 0-5 and 1-6.
        """

        for i in range(6):
            if ((self.board[i][0] == self.board[i][1] == self.board[i][2] == self.board[i][3] == self.board[i][4]) and self.board[i][0] != '-') or \
                    ((self.board[i][1] == self.board[i][2] == self.board[i][3] == self.board[i][4] == self.board[i][5]) and self.board[i][1] != '-'):
                return True

        """
        This code fragment checks for wins on columns.
        There are only two possible ways of winning on columns 0-5 and 1-6.
        """

        for i in range(6):
            if ((self.board[0][i] == self.board[1][i] == self.board[2][i] == self.board[3][i] == self.board[4][i]) and self.board[0][i] != '-') or \
                    ((self.board[1][i] == self.board[2][i] == self.board[3][i] == self.board[4][i] == self.board[5][i]) and self.board[1][i] != '-'):
                return True

        """
        This code fragment checks for wins on the main diagonal.
        There are only two possible ways of winning on the main diagonal, 0-5 and 1-6.
        """

        if ((self.board[0][0] == self.board[1][1] == self.board[2][2] == self.board[3][3] == self.board[4][4]) and self.board[0][0] != '-') or \
                ((self.board[1][1] == self.board[2][2] == self.board[3][3] == self.board[4][4] == self.board[5][5]) and self.board[1][1] != '-'):
            return True

        """
        This code fragment checks for wins on the secondary diagonal.
        There are only two possible ways of winning on the secondary diagonal, 0-5 and 1-6.
        """

        if ((self.board[0][5] == self.board[1][4] == self.board[2][3] == self.board[3][2] == self.board[4][1]) and self.board[0][5] != '-') or \
                ((self.board[1][4] == self.board[2][3] == self.board[3][2] == self.board[4][1] == self.board[5][0]) and self.board[5][0] != '-'):
            return True

        return False

    def get_board(self):
        return self.board[:]

    def print_board(self):
        for i in range(6):
            print(self.board[i])

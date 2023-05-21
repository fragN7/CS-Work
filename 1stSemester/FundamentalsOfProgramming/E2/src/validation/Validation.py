from src.errors.exceptions import ValidationError


class Validation:

    def __init__(self, board):
        self.board = board

    def move_validation(self, x, y, value):
        err = ""
        if x not in range(0, 6) or y not in range(0, 6) or value not in ['X', 'O']:
            raise ValidationError("Invalid entries")
        if err == "":
            valid_locations = self.board.get_valid_locations()
            if [x, y] not in valid_locations:
                raise ValidationError(f"The spot ({x+1}, {y+1}) is already used")

from src.errors.exception import ValidationError


class ValidateExpense(object):

    def validate(self, expense):
        err = ""
        if expense.get_day() not in range(1, 31):
            err += "Invalid day\n"
        if expense.get_amount() < 0:
            err += "Invalid amount\n"
        if expense.get_typ() == "":
            err += "Invalid type"
        if len(err) > 0:
            raise ValidationError(err)

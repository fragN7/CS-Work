from src.errors.exceptions import ValidationError


class ValidAssignment(object):

    @staticmethod
    def validate_assignment(assignment):
        err = ""
        if assignment.get_assignment_id() < 0:
            err = err + "Invalid ID\n"
        if assignment.get_description() == "":
            err = err + "Invalid description\n"
        deadline = assignment.get_deadline().split('/')
        if len(deadline) != 3 or ((deadline[1] == "2" or deadline[1] == "02") and
                                  (deadline[0] == "29" or deadline[0] == "30" or deadline[0] == "31")):
            err = err + "Invalid deadline\n"
        else:
            day = deadline[0]
            try:
                day = int(day)
            except ValueError:
                day = -1
            if day not in range(1, 32):
                err = err + "Invalid day\n"
            month = deadline[1]
            try:
                month = int(month)
            except ValueError:
                month = -1
            if month not in range(1, 13):
                err = err + "Invalid month\n"
            year = deadline[2]
            try:
                year = int(year)
            except ValueError:
                year = -1
            if year < 0:
                err = err + "Invalid year\n"
        if len(err) > 0:
            raise ValidationError(err)

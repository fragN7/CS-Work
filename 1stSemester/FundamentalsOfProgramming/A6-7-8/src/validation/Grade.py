import datetime

from src.errors.exceptions import ValidationError


class ValidGrade(object):

    @staticmethod
    def validate_grade(grade):
        err = ""
        if grade.get_student_id() < 0:
            err = err + "Invalid student ID\n"
        if grade.get_assignment_id() < 0:
            err = err + "Invalid assignment ID\n"
        if grade.get_grade() not in range(1, 11) and grade.get_grade() != "not graded yet":
            err = err + "Invalid grade value\n"
        if len(err) > 0:
            raise ValidationError(err)

    @staticmethod
    def check_deadline(assignment):
        deadline = assignment.get_deadline()
        deadline = deadline.split('/')
        deadline = datetime.datetime(int(deadline[2]), int(deadline[1]), int(deadline[0]))
        current_date = datetime.datetime.now()
        if deadline < current_date:
            return True
        return False

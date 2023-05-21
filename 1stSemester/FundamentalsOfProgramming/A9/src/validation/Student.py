from src.errors.exceptions import ValidationError


class ValidStudent(object):

    @staticmethod
    def validate_student(student):
        err = ""
        if student.get_student_id() < 0:
            err = err + "Invalid student ID\n"
        if student.get_name() == "":
            err = err + "Invalid Name\n"
        if student.get_group() == "":
            err = err + "Invalid group\n"
        if len(err) > 0:
            raise ValidationError(err)

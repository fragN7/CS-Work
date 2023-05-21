class Grade:

    def __init__(self, assignment, student, grade_value="not graded yet"):
        self.__assignment = assignment
        self.__student = student
        self.__grade_value = grade_value

    def get_assignment(self):
        return self.__assignment

    def get_assignment_id(self):
        return self.__assignment.get_assignment_id()

    def get_student(self):
        return self.__student

    def get_student_id(self):
        return self.__student.get_student_id()

    def get_grade(self):
        return self.__grade_value

    def set_grade(self, new_grade):
        self.__grade_value = new_grade

    def __str__(self):
        grade = self.__grade_value
        return "Assignment ID:" + str(self.__assignment.get_assignment_id()) \
               + " Student ID:" + str(self.__student.get_student_id()) + " Grade:" + str(grade)

    def __eq__(self, other):
        return self.__assignment.get_assignment_id() == other.__assignment.get_assignment_id() \
               and self.__student.get_student_id() == other.__student.get_student_id()

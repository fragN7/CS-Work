import random
from src.errors.exceptions import RepoError


class Population(object):

    def __init__(self, assignments, students, grades):
        self.__assignments = assignments
        self.__students = students
        self.__grades = grades

    def __add_student(self):
        student_name = ["Lionel", "Erling", "Zlatan", "Cristiano", "N'golo", "Luis", "Kylian", "Laurent",
                        "Luka", "Jan", "Andy", "Rafael", "Novak"]
        student_first_name = ["Messi", "Haaland", "Ibrahimovic", "Ronaldo", "Kante", "Suarez", "Mbappe",
                              "Koscielny", "Modric", "Oblak", "Murray", "Nadal", "Djokovic"]
        student_groups = ["911", "912", "913", "914", "915", "916", "917"]
        for i in range(1, 21):
            self.__students.add_student(i, random.choice(student_name) + " " + random.choice(student_first_name),
                                        random.choice(student_groups))

    def __add_assignments(self):
        assignment_names = ["FP", "CSA", "Logics", "Algebra", "Analysis"]
        assignment_dates = ["19/11/2021", "26/11/2021", "3/12/2021", "10/12/2021",
                            "17/12/2021", "17/11/2021", "23/11/2021"]
        for i in range(1, 21):
            self.__assignments.add_assignment(i, random.choice(assignment_names), random.choice(assignment_dates))

    def __add_grades(self):
        for i in range(1, 25):
            try:
                self.__grades.assign_student(random.randint(1, 20), random.randint(1, 20))
            except RepoError:
                continue

    def __grade_grades(self):
        grades_choices = ["not graded yet", 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00]
        grades = self.__grades.get_grades()
        for i in range(len(grades)):
            self.__grades.grade_assignment(grades[i].get_assignment_id(),
                                           grades[i].get_student_id(), random.choice(grades_choices))

    def populate_list(self):
        self.__add_student()
        self.__add_assignments()
        self.__add_grades()
        self.__grade_grades()

from src.domain.Grade import Grade
from src.errors.exceptions import RepoError
from src.domain.IterableStructure import gnome_sort, filtering


class ServiceGrade(object):

    def __init__(self, repo_grade, valid_grade, repo_student, repo_assignment):
        self.__repo_grade = repo_grade
        self.__valid_grade = valid_grade
        self.__repo_student = repo_student
        self.__repo_assignment = repo_assignment

    def add_grade(self, assignment, student, grade_value):
        grade = Grade(assignment, student, grade_value)
        self.__valid_grade.validate_grade(grade)
        self.__repo_grade.add(grade)

    def remove_grade(self, assignment, student):
        grade = self.__repo_grade.find_ids(assignment, student)
        self.__valid_grade.validate_grade(grade)
        self.__repo_grade.remove(grade)

    def find_grade(self, assignment_id, student_id):
        grades = self.__repo_grade.get_all_grades()
        for i in grades:
            if i.get_assignment_id() == assignment_id and i.get_student_id() == student_id:
                return i.get_grade()

    def assign_group(self, assignment_id, group):
        students = self.__repo_student.get_all_students()
        ok = False
        for i in students:
            if i.get_group() == group:
                try:
                    assignment = self.__repo_assignment.find_id(assignment_id)
                    grade = Grade(assignment, i)
                    self.__valid_grade.validate_grade(grade)
                    self.__repo_grade.add(grade)
                    ok = True
                except RepoError as err:
                    if not ok:
                        raise RepoError(err)

    def remove_assigned_group(self, assignment_id, group):
        grades = self.__repo_grade.get_all_grades()
        ok = True
        while ok:
            ok = False
            for i in grades:
                student = self.__repo_student.find_id(i.get_student_id())
                if student.get_group() == group and i.get_assignment_id() == assignment_id:
                    try:
                        self.__repo_grade.remove(i)
                        ok = True
                    except RepoError:
                        return

    def assign_student(self, assignment_id, student_id):
        students = self.__repo_student.get_all_students()
        for i in students:
            if i.get_student_id() == student_id:
                assignment = self.__repo_assignment.find_id(assignment_id)
                grade = Grade(assignment, i)
                self.__valid_grade.validate_grade(grade)
                self.__repo_grade.add(grade)

    def remove_assigned_student(self, assignment_id, student_id):
        assignment = self.__repo_assignment.find_id(assignment_id)
        student = self.__repo_student.find_id(student_id)
        grade = Grade(assignment, student)
        self.__repo_grade.remove(grade)

    def grade_assignment(self, assignment_id, student_id, new_grade):
        assignment = self.__repo_assignment.find_id(assignment_id)
        student = self.__repo_student.find_id(student_id)
        grade = Grade(assignment, student, new_grade)
        grades = self.__repo_grade.get_all_grades()
        if grade not in grades:
            raise RepoError("The student has not been assigned this assignment")
        for i in grades:
            if i == grade and i.get_grade() == "not graded yet":
                self.__repo_grade.update(grade)
                return
        raise RepoError("Assignment already graded")

    def un_grade_assignment(self, assignment_id, student_id):
        assignment = self.__repo_assignment.find_id(assignment_id)
        student = self.__repo_student.find_id(student_id)
        grade = Grade(assignment, student, "not graded yet")
        self.__repo_grade.update(grade)

    def remove_assignment_grades(self, assignment_id):
        assignment = self.__repo_assignment.find_id(assignment_id)
        grades = self.__repo_grade.get_all_grades()
        undo_list = []
        redo_list = []
        for i in grades:
            if assignment_id == i.get_assignment_id():
                self.__repo_grade.remove(i)
                undo_list.append(("add g", i))
                redo_list.append(("add g", i))
        self.__repo_assignment.remove(assignment)
        undo_list.append(("del a", assignment))
        redo_list.append(("del a", assignment))
        return undo_list, redo_list

    def remove_student_grades(self, student_id):
        student = self.__repo_student.find_id(student_id)
        grades = self.__repo_grade.get_all_grades()
        undo_list = []
        redo_list = []
        for i in grades:
            if student_id == i.get_student_id():
                self.__repo_grade.remove(i)
                undo_list.append(("add g", i))
                redo_list.append(("add g", i))
        self.__repo_student.remove(student)
        undo_list.append(("del s", student))
        redo_list.append(("del s", student))
        return undo_list, redo_list

    def filter_student(self, grade):
        if grade.get_student_id() == self.filtered_student.get_student_id():
            return True
        return False

    def filter_assignment(self, grade):
        if grade.get_assignment_id() == self.filtered_assignment.get_assignment_id():
            return True
        return False

    def filter_grades_student(self, student):
        self.filtered_student = student
        grades = self.__repo_grade.get_all_grades()
        grades = filtering(grades, self.filter_student)
        return grades[:]

    def filter_grades_assignment(self, assignment):
        self.filtered_assignment = assignment
        grades = self.__repo_grade.get_all_grades()
        grades = filtering(grades, self.filter_assignment)
        return grades[:]

    def get_descending_grade(self, assignment_id):
        student_list = []
        assignment = self.__repo_assignment.find_id(assignment_id)
        grades = self.filter_grades_assignment(assignment)
        for i in grades:
            temp_list = []
            if i.get_grade() != "not graded yet":
                student = i.get_student()
                temp_list.append(student)
                temp_list.append(i.get_grade())
                student_list.append(temp_list)
        # student_list.sort(key=lambda x: float(x[1]), reverse=True)
        gnome_sort(student_list, self.best_grades)
        return student_list[:]

    def get_late_students(self):
        student_list = []
        grades = self.__repo_grade.get_all_grades()
        for i in grades:
            assignment = i.get_assignment()
            if self.__valid_grade.check_deadline(assignment) and i.get_grade() == "not graded yet" \
                    and i.get_student() not in student_list:
                student = i.get_student()
                student_list.append(student)
        return student_list[:]

    def get_average_grade(self, student_id):
        sum_grades = 0.0
        num_grades = 0
        grades = self.__repo_grade.get_all_grades()
        for i in grades:
            if student_id == i.get_student_id() and i.get_grade() != "not graded yet":
                sum_grades = sum_grades + i.get_grade()
                num_grades = num_grades + 1
        if num_grades:
            return "{:.2f}".format(float(sum_grades/num_grades))
        return "no grades"

    @staticmethod
    def best_grades(student1, student2):
        student_grade1 = student1[1]
        student_grade2 = student2[1]
        return student_grade1 <= student_grade2

    def get_best_students(self):
        student_list = []
        grades = self.__repo_grade.get_all_grades()
        for i in grades:
            temp_list = []
            student = i.get_student()
            student_id = student.get_student_id()
            avg_grade = self.get_average_grade(student_id)
            temp_list.append(student)
            temp_list.append(avg_grade)
            if avg_grade != "no grades" and temp_list not in student_list:
                student_list.append(temp_list)
        # student_list.sort(key=lambda x: float(x[1]), reverse=True)
        gnome_sort(student_list, self.best_grades)
        return student_list[:len(student_list)//3]

    def get_grades(self):
        return self.__repo_grade.get_all_grades()

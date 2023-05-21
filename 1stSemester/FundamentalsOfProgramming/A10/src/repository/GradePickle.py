import pickle
from src.errors.exceptions import PickleError


class PickleGrade:

    def __init__(self, file_name):
        self.__fileName = file_name

    def __load_grades(self):
        file = open(self.__fileName, "rb")
        try:
            read_list = pickle.load(file)
        except EOFError:
            read_list = []
        file.close()
        return read_list[:]

    def __store_grades(self, read_list):
        file = open(self.__fileName, "wb")
        pickle.dump(read_list, file)
        file.close()

    def add(self, grade):
        grades = self.__load_grades()
        if grade in grades:
            raise PickleError("Grade already exists!")
        grades.append(grade)
        self.__store_grades(grades)

    def remove(self, grade):
        grades = self.__load_grades()
        if grade not in grades:
            raise PickleError("Grade doesnt exist!")
        for i in range(len(grades)):
            if grades[i] == grade:
                del grades[i]
                break
        self.__store_grades(grades)

    def update(self, grade):
        grades = self.__load_grades()
        if grade not in grades:
            raise PickleError("Grade doesnt exist!")
        for i in range(len(grades)):
            if grades[i] == grade:
                grades[i] = grade
                break
        self.__store_grades(grades)

    def remove_student_grade(self, student_id):
        grades = self.__load_grades()
        for i in range(len(grades)):
            if grades[i].get_student_id() == student_id:
                del grades[i]
                break
        self.__store_grades(grades)

    def remove_assignment_grade(self, assignment_id):
        grades = self.__load_grades()
        for i in range(len(grades)):
            if grades[i].get_assignment_id() == assignment_id:
                del grades[i]
                break
        self.__store_grades(grades)

    def get_all_grades(self):
        grades = self.__load_grades()
        return grades[:]

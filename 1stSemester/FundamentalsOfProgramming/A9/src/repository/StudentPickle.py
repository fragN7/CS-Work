import pickle
from src.errors.exceptions import PickleError
from src.domain.Student import Student


class PickleStudent:

    def __init__(self, file_name):
        self.__fileName = file_name

    def __load_students(self):
        file = open(self.__fileName, "rb")
        try:
            read_list = pickle.load(file)
        except EOFError:
            read_list = []
        file.close()
        return read_list[:]

    def __store_students(self, read_list):
        file = open(self.__fileName, "wb")
        pickle.dump(read_list, file)
        file.close()

    def add(self, student):
        students = self.__load_students()
        if student in students:
            raise PickleError("Student already exists!")
        students.append(student)
        self.__store_students(students)

    def remove(self, student):
        students = self.__load_students()
        if student not in students:
            raise PickleError("Student doesn't exist!")
        for i in range(len(students)):
            if students[i] == student:
                del students[i]
                break
        self.__store_students(students)

    def update(self, student):
        students = self.__load_students()
        if student not in students:
            raise PickleError("Student doesn't exist!")
        for i in range(len(students)):
            if students[i] == student:
                students[i] = student
                break
        self.__store_students(students)

    def find_id(self, student_id):
        students = self.__load_students()
        for student in students:
            if student.get_student_id() == student_id:
                return student
        raise PickleError("Student doesnt exist!")

    def store_something(self):
        self.__store_students([Student(9, "Paul George", "911"), Student(21, "Kevin Durant", "OKC")])

    def get_all_students(self):
        students = self.__load_students()
        return students[:]

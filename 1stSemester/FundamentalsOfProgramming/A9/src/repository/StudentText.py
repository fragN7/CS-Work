from src.errors.exceptions import TextFileError
from src.domain.IterableStructure import IterableStructure
from src.domain.Student import Student


class TextStudent:

    def __init__(self, file_name):
        self.__fileName = file_name

    def __read_students(self):
        file = open(self.__fileName, "r")
        content = file.readlines()
        students = IterableStructure()
        for line in content:
            line.strip()
            line = line.replace('\n', '')
            line = line.split('|')
            students.append(Student(int(line[0]), line[1], line[2]))
        file.close()
        return students

    def __write_students(self, students):
        file = open(self.__fileName, "w")
        for student in students:
            file.write(str(student.get_student_id()) + "|" + student.get_name() + "|" + str(student.get_group()) + "\n")
        file.close()

    def __len__(self):
        return len(self.__read_students())

    def add(self, student):
        students = self.__read_students()
        if student in students:
            raise TextFileError("Student already exists!")
        students.append(student)
        self.__write_students(students)

    def remove(self, student):
        students = self.__read_students()
        if student not in students:
            raise TextFileError("Student doesn't exist!")
        for i in range(len(students)):
            if students[i] == student:
                del students[i]
                break
        self.__write_students(students)

    def update(self, student):
        students = self.__read_students()
        if student not in students:
            raise TextFileError("Student doesn't exist!")
        for i in range(len(students)):
            if students[i] == student:
                students[i] = student
                break
        self.__write_students(students)

    def find_id(self, student_id):
        students = self.__read_students()
        for student in students:
            if student.get_student_id() == student_id:
                return student
        raise TextFileError("Student doesnt exist!")

    def get_all_students(self):
        students = self.__read_students()
        return_list = []
        for i in range(0, len(students)):
            return_list.append(students[i])
        return return_list[:]

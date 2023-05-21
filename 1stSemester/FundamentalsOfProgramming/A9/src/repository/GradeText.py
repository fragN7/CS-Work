from src.errors.exceptions import TextFileError
from src.domain.Grade import Grade
from src.domain.IterableStructure import IterableStructure


class TextGrade:

    def __init__(self, file_name, text_repo_student, text_repo_assignments):
        self.__fileName = file_name
        self.__fileRepoStudents = text_repo_student
        self.__fileRepoAssignments = text_repo_assignments

    def __read_grades(self):
        file = open(self.__fileName, "r")
        content = file.readlines()
        grades = IterableStructure()
        for line in content:
            line.strip()
            line = line.replace('\n', '')
            line = line.split('|')
            student = self.__fileRepoStudents.find_id(int(line[1]))
            assignment = self.__fileRepoAssignments.find_id(int(line[0]))
            grades.append(Grade(assignment, student, line[2]))
        file.close()
        return grades

    def __write_grades(self, grades):
        file = open(self.__fileName, "w")
        for grade in grades:
            file.write(
                str(grade.get_assignment_id()) + "|" + str(grade.get_student_id()) + "|" + str(grade.get_grade()) + "\n")
        file.close()

    def add(self, grade):
        grades = self.__read_grades()
        if grade in grades:
            raise TextFileError("Element already exists!")
        grades.append(grade)
        self.__write_grades(grades)

    def remove(self, grade):
        grades = self.__read_grades()
        if grade not in grades:
            raise TextFileError("Element doesnt exist!")
        for i in range(len(grades)):
            if grades[i] == grade:
                del grades[i]
                break
        self.__write_grades(grades)

    def update(self, grade):
        grades = self.__read_grades()
        if grade not in grades:
            raise TextFileError("Element doesnt exist!")
        for i in range(len(grades)):
            if grades[i] == grade:
                grades[i] = grade
                break
        self.__write_grades(grades)

    def remove_student_grades(self, student_id):
        grades = self.__read_grades()
        for i in range(len(grades)):
            if grades[i].getStudentID() == student_id:
                del grades[i]
                break
        self.__write_grades(grades)

    def remove_assignment_grades(self, assignment_id):
        grades = self.__read_grades()
        for i in range(len(grades)):
            if grades[i].getAssignmentID() == assignment_id:
                del grades[i]
                break
        self.__write_grades(grades)

    def get_all_grades(self):
        grades = self.__read_grades()
        return_list = []
        for i in range(0, len(grades)):
            return_list.append(grades[i])
        return return_list[:]

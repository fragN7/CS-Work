from src.domain.Student import Student
from src.errors.exceptions import RepoError


class ServiceStudent(object):
    
    def __init__(self, repo_student, valid_student):
        self.__repo_student = repo_student
        self.__valid_student = valid_student

    def add_student(self, student_id, name, group):
        student = Student(student_id, name, group)
        self.__valid_student.validate_student(student)
        self.__repo_student.add(student)

    def remove_student(self, student_id):
        student = self.__repo_student.find_id(student_id)
        self.__valid_student.validate_student(student)
        self.__repo_student.remove(student)

    def update_student(self, student_id, name, new_group):
        student = Student(student_id, name, new_group)
        self.__valid_student.validate_student(student)
        self.__repo_student.update(student)

    def find_student_id(self, student_id):
        try:
            return self.__repo_student.find_id(student_id)
        except RepoError:
            raise RepoError

    def get_students(self):
        return self.__repo_student.get_all_students()

from src.errors.exceptions import RepoError


class RepoStudent:

    def __init__(self):
        self.__repo_students = []

    def __len__(self):
        return len(self.__repo_students)

    def add(self, student):
        if student in self.__repo_students:
            raise RepoError("Student already exists")
        self.__repo_students.append(student)

    def find_id(self, student_id):
        for i in self.__repo_students:
            if i.get_student_id() == student_id:
                return i
        raise RepoError("Student doesn't exist")

    def update(self, student):
        if student not in self.__repo_students:
            raise RepoError("Student doesn't exist")
        for i in range(len(self.__repo_students)):
            if self.__repo_students[i] == student:
                self.__repo_students[i] = student
                return

    def remove(self, student):
        if student not in self.__repo_students:
            raise RepoError("Student doesn't exist")
        for i in range(len(self.__repo_students)):
            if self.__repo_students[i] == student:
                del self.__repo_students[i]
                return

    def get_all_students(self):
        return self.__repo_students[:]

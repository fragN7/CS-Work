from src.errors.exceptions import RepoError


class RepoGrade:

    def __init__(self):
        self.__repo_grades = []

    def __len__(self):
        return len(self.__repo_grades)

    def add(self, grade):
        if grade in self.__repo_grades:
            raise RepoError("Grade already exists")
        self.__repo_grades.append(grade)

    def find_ids(self, assignment, student):
        for i in self.__repo_grades:
            if i.get_assignment() == assignment and i.get_student() == student:
                return i
        raise RepoError("Grade doesn't exist")

    def update(self, grade):
        if grade not in self.__repo_grades:
            raise RepoError("Grade doesn't exist")
        for i in range(len(self.__repo_grades)):
            if self.__repo_grades[i] == grade:
                self.__repo_grades[i] = grade
                return

    def remove(self, grade):
        if grade not in self.__repo_grades:
            raise RepoError("Grade doesn't exist")
        for i in range(len(self.__repo_grades)):
            if self.__repo_grades[i] == grade:
                del self.__repo_grades[i]
                return

    def get_all_grades(self):
        return self.__repo_grades[:]

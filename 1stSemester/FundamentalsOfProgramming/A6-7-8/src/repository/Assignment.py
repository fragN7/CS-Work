from src.errors.exceptions import RepoError


class RepoAssignment:

    def __init__(self):
        self.__repo_assignments = []

    def __len__(self):
        return len(self.__repo_assignments)

    def add(self, assignment):
        if assignment in self.__repo_assignments:
            raise RepoError("Assignment already exists")
        self.__repo_assignments.append(assignment)

    def find_id(self, assignment_id):
        for i in self.__repo_assignments:
            if i.get_assignment_id() == assignment_id:
                return i
        raise RepoError("Assignment doesn't exist")

    def update(self, assignment):
        if assignment not in self.__repo_assignments:
            raise RepoError("Assignment doesn't exist")
        for i in range(len(self.__repo_assignments)):
            if self.__repo_assignments[i] == assignment:
                self.__repo_assignments[i] = assignment
                return

    def remove(self, assignment):
        if assignment not in self.__repo_assignments:
            raise RepoError("Assignment doesn't exist")
        for i in range(len(self.__repo_assignments)):
            if self.__repo_assignments[i] == assignment:
                del self.__repo_assignments[i]
                return

    def get_all_assignments(self):
        return self.__repo_assignments[:]

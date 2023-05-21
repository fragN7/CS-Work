from src.domain.Assignment import Assignment
from src.errors.exceptions import RepoError


class ServiceAssignment(object):

    def __init__(self, repo_assignment, valid_assignment):
        self.__repo_assignment = repo_assignment
        self.__valid_assignment = valid_assignment

    def add_assignment(self, assignment_id, description, deadline):
        assignment = Assignment(assignment_id, description, deadline)
        self.__valid_assignment.validate_assignment(assignment)
        self.__repo_assignment.add(assignment)

    def remove_assignment(self, assignment_id):
        assignment = self.__repo_assignment.find_id(assignment_id)
        self.__valid_assignment.validate_assignment(assignment)
        self.__repo_assignment.remove(assignment)

    def update_assignment(self, assignment_id, description, new_deadline):
        assignment = Assignment(assignment_id, description, new_deadline)
        self.__valid_assignment.validate_assignment(assignment)
        self.__repo_assignment.update(assignment)

    def find_assignment_id(self, assignment_id):
        try:
            return self.__repo_assignment.find_id(assignment_id)
        except RepoError:
            raise RepoError

    def get_assignments(self):
        return self.__repo_assignment.get_all_assignments()

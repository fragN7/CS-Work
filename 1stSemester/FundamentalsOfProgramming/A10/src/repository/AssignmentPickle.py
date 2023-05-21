import pickle
from src.errors.exceptions import PickleError
from src.domain.Assignment import Assignment


class PickleAssignment:

    def __init__(self, file_name):
        self.__fileName = file_name

    def __load_assignments(self):
        file = open(self.__fileName, "rb")
        try:
            read_list = pickle.load(file)
        except EOFError:
            read_list = []
        file.close()
        return read_list

    def __store_assignments(self, read_list):
        file = open(self.__fileName, "wb")
        pickle.dump(read_list, file)
        file.close()

    def add(self, assignment):
        assignments = self.__load_assignments()
        if assignment in assignments:
            raise PickleError("Assignment already exists")
        assignments.append(assignment)
        self.__store_assignments(assignments)

    def remove(self, assignment):
        assignments = self.__load_assignments()
        if assignment not in assignments:
            raise PickleError("Assignment doesn't exist")
        for i in range(len(assignments)):
            if assignments[i] == assignment:
                del assignments[i]
                break
        self.__store_assignments(assignments)

    def update(self, assignment):
        assignments = self.__load_assignments()
        if assignment not in assignments:
            raise PickleError("Assignment doesn't exist")
        for i in range(len(assignments)):
            if assignments[i] == assignment:
                assignments[i] = assignment
                break
        self.__store_assignments(assignments)

    def get_all_assignments(self):
        assignments = self.__load_assignments()
        return assignments[:]

    def store_something(self):
        self.__store_assignments([Assignment(14, "FP", "19/12/2022"), Assignment(21, "Logics", "31/10/2021")])

    def find_id(self, assignment_id):
        assignments = self.__load_assignments()
        for i in assignments:
            if assignment_id == i.get_assignment_id():
                return i
        raise PickleError("Assignment doesn't exist")

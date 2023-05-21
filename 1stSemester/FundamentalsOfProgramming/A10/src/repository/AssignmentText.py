from src.errors.exceptions import TextFileError
from src.domain.IterableStructure import IterableStructure
from src.domain.Assignment import Assignment


class TextAssignment:

    def __init__(self, file_name):
        self.__fileName = file_name

    def __read_assignments(self):
        file = open(self.__fileName, "r")
        content = file.readlines()
        assignments = IterableStructure()
        for line in content:
            line.strip()
            line = line.replace('\n', '')
            line = line.split('|')
            assignments.append(Assignment(int(line[0]), line[1], line[2]))
        file.close()
        return assignments

    def __write_assignments(self, assignments):
        file = open(self.__fileName, "w")
        for assignment in assignments:
            file.write(str(assignment.get_assignment_id()) + "|" + assignment.get_description() + "|" +
                       assignment.get_deadline() + "\n")
        file.close()

    def add(self, assignment):
        assignments = self.__read_assignments()
        if assignment in assignments:
            raise TextFileError("Assignment already exists!")
        assignments.append(assignment)
        self.__write_assignments(assignments)

    def remove(self, assignment):
        assignments = self.__read_assignments()
        if assignment not in assignments:
            raise TextFileError("Assignment doesn't exist!")
        for i in range(len(assignments)):
            if assignments[i] == assignment:
                del assignments[i]
                break
        self.__write_assignments(assignments)

    def update(self, assignment):
        assignments = self.__read_assignments()
        if assignment not in assignments:
            raise TextFileError("Assignment doesn't exist!")
        for i in range(len(assignments)):
            if assignments[i] == assignment:
                assignments[i] = assignment
                break
        self.__write_assignments(assignments)

    def find_id(self, assignment_id):
        assignments = self.__read_assignments()
        for assignment in assignments:
            if assignment.get_assignment_id() == assignment_id:
                return assignment
        raise TextFileError("Assignment doesnt exist!")

    def get_all_assignments(self):
        assignments = self.__read_assignments()
        return_list = []
        for i in range(0, len(assignments)):
            return_list.append(assignments[i])
        return return_list[:]

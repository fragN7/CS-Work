from src.domain.expense import IterableStructure, Expense


class RepoExpense(object):

    def __init__(self):
        self.__expenses = []
        self.__undo_list = [[]]

    def __len__(self):
        return len(self.__expenses)

    def add_expense(self, expense):
        self.__expenses.append(expense)

    def remove_expense(self, expense):
        self.__expenses.remove(expense)

    def get_expenses(self):
        return self.__expenses[:]

    def add_to_undo_list(self):
        self.__undo_list.append(self.get_expenses())

    def delete_undo_list(self):
        self.__undo_list.pop()

    def add_to_new_list(self):
        self.__expenses = self.__undo_list[-2].copy()


class RepoTextExpense:

    def __init__(self, file_name):
        self.file_name = file_name

    def __read_expenses(self):
        file = open(self.file_name, "r")
        content = file.readlines()
        expenses = IterableStructure()
        for line in content:
            line = file.readline()
            line.strip()
            line = line.replace('\n', '')
            line.split(';')
            expenses.append(Expense(int(line[0]), line[1], line[2]))
        file.close()
        return expenses

    def __write_expenses(self, expenses):
        file = open(self.file_name, "w")
        for i in expenses:
            file.write(i.__str__())
        file.close()

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


from src.errors.exceptions import UndoError


class UndoRedo(object):

    def __init__(self, service_assignment, service_grade, service_student):
        self.__service_assignment = service_assignment
        self.__service_grade = service_grade
        self.__service_student = service_student
        self.__undo = []
        self.__undo_save = []
        self.__redo = []
        self.__redo_save = []
        self.__undo_actions = {"add a": self.__undo_add_assignment,
                               "add s": self.__undo_add_student,
                               "add g": self.__undo_add_grade,

                               "del a": self.__undo_remove_assignment,
                               "del s": self.__undo_remove_student,

                               "delete": self.__undo_deletes,

                               "up a": self.__undo_update_assignment,
                               "up g": self.__undo_update_grade,
                               "up s": self.__undo_update_student,

                               "as s": self.__undo_assign_student,
                               "as g": self.__undo_assign_group
                               }
        self.__redo_actions = {"add a": self.__redo_add_assignment,
                               "add s": self.__redo_add_student,
                               "add g": self.__redo_add_grade,

                               "del a": self.__redo_remove_assignment,
                               "del s": self.__redo_remove_student,

                               "delete": self.__redo_deletes,

                               "up a": self.__redo_update_assignment,
                               "up g": self.__redo_update_grade,
                               "up s": self.__redo_update_student,

                               "as s": self.__redo_assign_student,
                               "as g": self.__redo_assign_group,
                               }

    """
    Undo functions.
    """

    def add_to_undo_list(self, action, command):
        self.__undo.append((action, command))

    @staticmethod
    def get_undo_action(undo_unit):
        return undo_unit[0]

    @staticmethod
    def get_undo_command(undo_unit):
        return undo_unit[1]

    def service_undo(self):
        if not self.__undo:
            raise UndoError("Can not undo anymore")
        if self.__redo_save:
            self.__redo.append(self.__redo_save.pop(0))
        last_undo = self.__undo.pop()
        action = self.get_undo_action(last_undo)
        command = self.get_undo_command(last_undo)
        if action in self.__undo_actions:
            self.__undo_actions[action](command)
        self.__undo_save.append(last_undo)

    def __undo_add_assignment(self, assignment):
        self.__service_assignment.remove_assignment(assignment.get_assignment_id())

    def __undo_add_student(self, student):
        self.__service_student.remove_student(student.get_student_id())

    def __undo_remove_assignment(self, assignment):
        self.__service_assignment.add_assignment(assignment.get_assignment_id(), assignment.get_description(),
                                                 assignment.get_deadline())

    def __undo_remove_student(self, student):
        self.__service_student.add_student(student.get_student_id(), student.get_name(), student.get_group())

    def __undo_update_assignment(self, assignment):
        self.__service_assignment.update_assignment(assignment.get_assignment_id(),
                                                    assignment.get_description(), assignment.get_deadline())

    def __undo_update_student(self, student):
        self.__service_student.update_student(student.get_student_id(), student.get_name(), student.get_group())

    def __undo_assign_student(self, codes):
        self.__service_grade.remove_assigned_student(codes[0], codes[1])

    def __undo_assign_group(self, codes):
        self.__service_grade.remove_assigned_group(codes[0], codes[1])

    def __undo_update_grade(self, codes):
        self.__service_grade.un_grade_assignment(codes[0], codes[1])

    def __undo_add_grade(self, grade):
        self.__service_grade.add_grade(grade.get_assignment(), grade.get_student(), grade.get_grade())

    def __undo_deletes(self, operations):
        while operations:
            undo = operations.pop()
            action = self.get_undo_action(undo)
            command = self.get_undo_command(undo)
            self.__undo_actions[action](command)

    def get_undo(self):
        return self.__undo[:]

    """
    Redo functions.
    """

    def add_to_redo_list(self, action, command):
        self.__redo.append((action, command))

    @staticmethod
    def get_redo_action(redo_unit):
        return redo_unit[0]

    @staticmethod
    def get_redo_command(redo_unit):
        return redo_unit[1]

    def service_redo(self):
        if not self.__redo:
            raise UndoError("Can not redo anymore")
        if self.__undo_save:
            self.__undo.append(self.__undo_save.pop(0))
        last_redo = self.__redo.pop()
        action = self.get_redo_action(last_redo)
        command = self.get_undo_command(last_redo)
        if action in self.__redo_actions:
            self.__redo_actions[action](command)
        self.__redo_save.append(last_redo)

    def __redo_add_assignment(self, assignment):
        self.__service_assignment.add_assignment(assignment.get_assignment_id(), assignment.get_description(),
                                                 assignment.get_deadline())

    def __redo_add_student(self, student):
        self.__service_student.add_student(student.get_student_id(), student.get_name(), student.get_group())

    def __redo_remove_assignment(self, assignment):
        self.__service_assignment.remove_assignment(assignment.get_assignment_id())

    def __redo_remove_student(self, student):
        self.__service_student.remove_student(student.get_student_id())

    def __redo_update_assignment(self, assignment):
        self.__service_assignment.update_assignment(assignment.get_assignment_id(), assignment.get_deadline(),
                                                    assignment.get_deadline())

    def __redo_update_student(self, student):
        self.__service_student.update_student(student.get_student_id(), student.get_name(), student.get_group())

    def __redo_update_grade(self, grade):
        self.__service_grade.grade_assignment(grade[0], grade[1], grade[2])

    def __redo_assign_student(self, assign):
        self.__service_grade.assign_student(assign[0], assign[1])

    def __redo_assign_group(self, assign):
        self.__service_grade.assign_group(assign[0], assign[1])

    def __redo_add_grade(self, grade):
        self.__service_grade.remove_grade(grade.get_assignment(), grade.get_student())

    def __redo_deletes(self, operations):
        while operations:
            redo = operations.pop()
            action = self.get_redo_action(redo)
            command = self.get_redo_command(redo)
            self.__redo_actions[action](command)

    def get_redo(self):
        return self.__redo[:]

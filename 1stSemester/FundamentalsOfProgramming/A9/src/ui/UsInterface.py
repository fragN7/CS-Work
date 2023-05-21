from src.errors.exceptions import RepoError, ValidationError, UndoError, PickleError, TextFileError
from src.domain.Assignment import Assignment
from src.domain.Student import Student


class UserInterface:

    def __init__(self, service_student, service_assignment, service_grade, undo_redo):
        self.__service_student = service_student
        self.__service_assignment = service_assignment
        self.__service_grade = service_grade
        self.__undo_redo = undo_redo
        self.__cmd_choices = {"add student": self.__ui_add_student,
                              "add assignment": self.__ui_add_assignment,
                              "remove student": self.__ui_remove_student,
                              "remove assignment": self.__ui_remove_assignment,
                              "update student": self.__ui_update_student,
                              "update assignment": self.__ui_update_assignment,
                              "list students": self.__ui_list_students,
                              "list assignments": self.__ui_list_assignments,
                              "assign group": self.__ui_assign_group,
                              "assign student": self.__ui_assign_student,
                              "list grades": self.__ui_list_grades,
                              "grade assignment": self.__ui_grade_assignment,
                              "show stats": self.__ui_print_statistics,
                              "undo": self.__undo,
                              "redo": self.__redo
                              }

    def __ui_add_student(self):
        student_id = int(input("ID: "))
        name = input("Name: ")
        group = input("Group :")
        self.__service_student.add_student(student_id, name, group)
        student = Student(student_id, name, group)
        self.__undo_redo.add_to_undo_list("add s", student)
        self.__undo_redo.add_to_redo_list("add s", student)

    def __ui_add_assignment(self):
        assignment_id = int(input("ID: "))
        description = input("Description: ")
        deadline = input("Deadline: ")
        self.__service_assignment.add_assignment(assignment_id, description, deadline)
        assignment = Assignment(assignment_id, description, deadline)
        self.__undo_redo.add_to_undo_list("add a", assignment)
        self.__undo_redo.add_to_redo_list("add a", assignment)

    def __ui_remove_student(self):
        student_id = int(input("ID: "))
        undo_redo = self.__service_grade.remove_student_grades(student_id)
        self.__undo_redo.add_to_undo_list("delete", undo_redo[0])
        self.__undo_redo.add_to_redo_list("delete", undo_redo[1])

    def __ui_remove_assignment(self):
        assignment_id = int(input("ID: "))
        undo_redo = self.__service_grade.remove_assignment_grades(assignment_id)
        self.__undo_redo.add_to_undo_list("delete", undo_redo[0])
        self.__undo_redo.add_to_redo_list("delete", undo_redo[1])

    def __ui_update_student(self):
        student_id = int(input("ID: "))
        name = input("Name: ")
        group = input("Group: ")
        old_student = self.__service_student.find_student_id(student_id)
        self.__service_student.update_student(student_id, name, group)
        new_student = self.__service_student.find_student_id(student_id)
        self.__undo_redo.add_to_undo_list("up s", old_student)
        self.__undo_redo.add_to_redo_list("up s", new_student)

    def __ui_update_assignment(self):
        assignment_id = int(input("ID: "))
        description = input("Description: ")
        deadline = input("Deadline: ")
        old_assignment = self.__service_assignment.find_assignment_id(assignment_id)
        self.__service_assignment.update_assignment(assignment_id, description, deadline)
        new_assignment = self.__service_assignment.find_assignment_id(assignment_id)
        self.__undo_redo.add_to_undo_list("up a", old_assignment)
        self.__undo_redo.add_to_redo_list("up a", new_assignment)

    def __ui_list_students(self):
        students = self.__service_student.get_students()
        if not students:
            print("No students")
            return
        for i in students:
            print(i)

    def __ui_list_assignments(self):
        assignments = self.__service_assignment.get_assignments()
        if not assignments:
            print("No assignments")
            return
        for i in assignments:
            print(i)

    def __ui_assign_student(self):
        assignment_id = int(input("Assignment ID: "))
        student_id = int(input("Student ID: "))
        self.__service_grade.assign_student(assignment_id, student_id)
        self.__undo_redo.add_to_undo_list("as s", (assignment_id, student_id))
        self.__undo_redo.add_to_redo_list("as s", (assignment_id, student_id))

    def __ui_assign_group(self):
        assignment_id = int(input("Assignment ID: "))
        group = input("Group: ")
        self.__service_grade.assign_group(assignment_id, group)
        self.__undo_redo.add_to_undo_list("as g", (assignment_id, group))
        self.__undo_redo.add_to_redo_list("as g", (assignment_id, group))

    def __ui_list_grades(self):
        grades = self.__service_grade.get_grades()
        if not grades:
            print("No grades so far")
            return
        for i in grades:
            print(i)

    def __ui_grade_assignment(self):
        assignment_id = int(input("Assignment ID: "))
        student_id = int(input("Student ID: "))
        new_grade = float(input("Grade: "))
        self.__service_grade.grade_assignment(assignment_id, student_id, new_grade)
        self.__undo_redo.add_to_undo_list("up g", (assignment_id, student_id))
        self.__undo_redo.add_to_redo_list("up g", (assignment_id, student_id, new_grade))

    def __ui_print_statistics(self):
        print("\nCurrent stats:")
        assignment_id = int(input("Enter an assignment ID, to see the best grades for this assignment: "))
        descending_grade_list = self.__service_grade.get_descending_grade(assignment_id)
        if len(descending_grade_list) == 0:
            print("No students have this assignment")
        else:
            for student_grade in descending_grade_list:
                print(str(student_grade[0]) + " Grade:" + str(student_grade[1]))

        print("\nAll late students: ")
        late_students_list = self.__service_grade.get_late_students()
        if len(late_students_list) == 0:
            print("No late students")
        else:
            for student in late_students_list:
                print(student)

        print("\nBest students: ")
        best_school_situation = self.__service_grade.get_best_students()
        for student_grade in best_school_situation:
            print(str(student_grade[0]) + " Grade:" + str(student_grade[1]))

    def __undo(self):
        self.__undo_redo.service_undo()

    def __redo(self):
        self.__undo_redo.service_redo()

    @staticmethod
    def __print_cmd_menu():
        print("Welcome to the catalogue!!!\nHere are your options :\n")
        print("'add student': Add a student to the list")
        print("'remove student': Remove a student from the list")
        print("'update student': Update a student")
        print("'list students': List all students")
        print("------------------------------------------------------")
        print("'add assignment': Add a assignment to the list")
        print("'remove assignment': Remove a assignment from the list")
        print("'update assignment': Update a assignment")
        print("'list assignments': List all assignments")
        print("------------------------------------------------------")
        print("'assign student': Assign a assignment to a student")
        print("'assign group': Assign a assignment to a group")
        print("'grade assignment': Grade a assignment from a student")
        print("'list grades': List all grades")
        print("------------------------------------------------------")
        print("'show stats': Show statistics")
        print("'undo': Undo the last operation")
        print("'redo': Redo the last operation")
        print("'exit': Exit the catalogue\n")

    def run_ui(self):
        self.__print_cmd_menu()
        while True:
            cmd = input("Please write your command here: ").lower()
            if cmd == "exit":
                return None
            elif cmd == "":
                continue
            elif cmd in self.__cmd_choices:
                try:
                    self.__cmd_choices[cmd]()
                except ValueError:
                    print("Invalid numerical value")
                except ValidationError as ve:
                    print(ve)
                except RepoError as re:
                    print(re)
                except UndoError as ue:
                    print(ue)
                except PickleError as pe:
                    print(pe)
                except TextFileError as tfe:
                    print(tfe)
            else:
                print("Invalid command")

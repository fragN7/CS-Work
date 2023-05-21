import unittest

from src.domain.Assignment import Assignment
from src.domain.Grade import Grade
from src.domain.Student import Student

from src.validation.Assignment import ValidAssignment
from src.validation.Grade import ValidGrade
from src.validation.Student import ValidStudent

from src.errors.exceptions import ValidationError
from src.errors.exceptions import RepoError

from src.services.Assignment import ServiceAssignment
from src.repository.Assignment import RepoAssignment

from src.services.Student import ServiceStudent
from src.repository.Student import RepoStudent

from src.services.Grade import ServiceGrade
from src.repository.Grade import RepoGrade

from src.services.UndoRedo import UndoRedo


class TestDomain(unittest.TestCase):

    def setUp(self):
        assignment_id = 121
        description = "physics"
        deadline = "11/09/2029"
        self.__test_assignment = Assignment(assignment_id, description, deadline)
        assignment = self.__test_assignment

        student_id = 12
        name = "Rick Priceless"
        group = "912"
        self.__test_student = Student(student_id, name, group)
        student = self.__test_student

        grade_value = 9
        self.__test_grade = Grade(assignment, student, grade_value)

    def testAssignmentDomain(self):
        self.assertEqual(self.__test_assignment.get_assignment_id(), 121)
        self.assertEqual(self.__test_assignment.get_description(), "physics")
        self.assertEqual(self.__test_assignment.get_deadline(), "11/09/2029")

        new_description = "Drake"
        self.__test_assignment.set_description(new_description)
        self.assertEqual(self.__test_assignment.get_description(), new_description)

        new_deadline = "19/12/2002"
        self.__test_assignment.set_deadline(new_deadline)
        self.assertEqual(self.__test_assignment.get_deadline(), new_deadline)

        other_id = 121
        other_description = "maths"
        other_deadline = "09/04/2011"
        other_assignment = Assignment(other_id, other_description, other_deadline)

        self.assertTrue(self.__test_assignment.__eq__(other_assignment))
        self.assertEqual(self.__test_assignment.__str__(), "Assignment ID:121 Description:Drake Deadline:19/12/2002")

    def testGradeDomain(self):
        self.assertEqual(self.__test_grade.get_assignment(), self.__test_assignment)
        self.assertEqual(self.__test_grade.get_assignment_id(), 121)
        self.assertEqual(self.__test_grade.get_student(), self.__test_student)
        self.assertEqual(self.__test_grade.get_student_id(), 12)
        self.assertEqual(self.__test_grade.get_grade(), 9)

        new_grade_value = 6
        self.__test_grade.set_grade(new_grade_value)
        self.assertEqual(self.__test_grade.get_grade(), new_grade_value)

        other_assignment_id = 121
        other_description = "maths"
        other_deadline = "09/04/2011"
        other_assignment = Assignment(other_assignment_id, other_description, other_deadline)

        other_student_id = 12
        other_name = "Maya Jama"
        other_group = "Miguel group"
        other_student = Student(other_student_id, other_name, other_group)

        other_grade_value = 7
        other_grade = Grade(other_assignment, other_student, other_grade_value)

        self.assertTrue(self.__test_grade.__eq__(other_grade))
        self.assertEqual(self.__test_grade.__str__(), "Assignment ID:121 Student ID:12 Grade:6")

    def testStudentDomain(self):
        self.assertEqual(self.__test_student.get_student_id(), 12)
        self.assertEqual(self.__test_student.get_name(), "Rick Priceless")
        self.assertEqual(self.__test_student.get_group(), "912")

        new_name = "Drake"
        self.__test_student.set_name(new_name)
        self.assertEqual(self.__test_student.get_name(), new_name)

        new_group = "913"
        self.__test_student.set_group(new_group)
        self.assertEqual(self.__test_student.get_group(), new_group)

        other_student_id = 12
        other_name = "Maya Jama"
        other_group = "Miguel group"
        other_student = Student(other_student_id, other_name, other_group)

        self.assertTrue(self.__test_student.__eq__(other_student))
        self.assertEqual(self.__test_student.__str__(), "Student ID:12 Name:Drake Group:913")


class TestValidation(unittest.TestCase):

    def setUp(self):
        self.__valid_assignment = ValidAssignment()
        self.__valid_grade = ValidGrade()
        self.__valid_student = ValidStudent()

    def testAssignmentValidation(self):
        assignment = Assignment(-4, "dudes", "15/02/2030")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid ID\n")

        assignment = Assignment(4, "", "15/02/2030")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid description\n")

        assignment = Assignment(12, "dudes", "12/02/-41")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid year\n")

        assignment = Assignment(12, "dudes", "30/02/2002")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid deadline\n")

        assignment = Assignment(12, "dudes", "29/02/2022")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid deadline\n")

        assignment = Assignment(12, "dudes", "0/0/0")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid day\nInvalid month\n")

        assignment = Assignment(-1, "", "0/0/0/0")
        with self.assertRaises(ValidationError) as ve:
            self.__valid_assignment.validate_assignment(assignment)
        self.assertEqual(str(ve.exception), "Invalid ID\nInvalid description\nInvalid deadline\n")

    def testGradeValidation(self):
        assignment_id = -4
        description = "maths"
        deadline = "09/04/2011"
        assignment = Assignment(assignment_id, description, deadline)

        student_id = 12
        name = "Maya Jama"
        group = "Miguel group"
        student = Student(student_id, name, group)

        grade = Grade(assignment, student, 8)
        with self.assertRaises(ValidationError):
            self.__valid_grade.validate_grade(grade)

        assignment_id = 4
        description = "maths"
        deadline = "09/04/2011"
        assignment = Assignment(assignment_id, description, deadline)

        student_id = -12
        name = "Maya Jama"
        group = "Miguel group"
        student = Student(student_id, name, group)

        grade = Grade(assignment, student, 8)
        with self.assertRaises(ValidationError):
            self.__valid_grade.validate_grade(grade)

        assignment_id = 4
        description = "maths"
        deadline = "09/04/2022"
        assignment = Assignment(assignment_id, description, deadline)

        student_id = 12
        name = "Maya Jama"
        group = "Miguel group"
        student = Student(student_id, name, group)

        grade = Grade(assignment, student, 12)
        with self.assertRaises(ValidationError):
            self.__valid_grade.validate_grade(grade)

        assignment_id = 7
        description = "maths"
        deadline = "09/04/2011"
        assignment_1 = Assignment(assignment_id, description, deadline)

        self.assertFalse(self.__valid_grade.check_deadline(assignment))
        self.assertTrue(self.__valid_grade.check_deadline(assignment_1))

    def testStudentValidation(self):
        student = Student(-1, "Ronaldo", "Barcelona")
        with self.assertRaises(ValidationError):
            self.__valid_student.validate_student(student)

        student = Student(-1, "", "Barcelona")
        with self.assertRaises(ValidationError):
            self.__valid_student.validate_student(student)

        student = Student(-1, "Ronaldo", "")
        with self.assertRaises(ValidationError):
            self.__valid_student.validate_student(student)


class TestRepo(unittest.TestCase):

    def setUp(self):
        self.__repo_assignment = RepoAssignment()
        self.__repo_grades = RepoGrade()
        self.__repo_student = RepoStudent()

    def testAssignmentRepo(self):
        assignment_id = 121
        description = "physics"
        deadline = "11/09/2029"
        assignment = Assignment(assignment_id, description, deadline)

        """
        Test for adding an assignment.
        """

        self.assertEqual(self.__repo_assignment.__len__(), 0)
        self.__repo_assignment.add(assignment)
        self.assertEqual(self.__repo_assignment.__len__(), 1)

        with self.assertRaises(RepoError) as re:
            self.__repo_assignment.add(assignment)
        self.assertEqual(str(re.exception), "Assignment already exists")

        """
        Test for finding an assignment.
        """

        self.assertTrue(self.__repo_assignment.find_id(121), assignment)

        some_id = 99
        with self.assertRaises(RepoError) as re:
            self.__repo_assignment.find_id(some_id)
        self.assertEqual(str(re.exception), "Assignment doesn't exist")

        update_id = 121
        update_description = "UBB"
        update_deadline = "14/12/2001"
        update_assignment = Assignment(update_id, update_description, update_deadline)

        """
        Test for updating and removing an assignment.
        """

        assignment_id = 99
        description = "lol"
        deadline = "19/04/2001"
        some_assignment = Assignment(assignment_id, description, deadline)

        self.assertEqual(self.__repo_assignment.__len__(), 1)
        self.__repo_assignment.update(update_assignment)

        with self.assertRaises(RepoError) as re:
            self.__repo_assignment.update(some_assignment)
        self.assertEqual(str(re.exception), "Assignment doesn't exist")

        self.__repo_assignment.remove(update_assignment)
        self.assertEqual(self.__repo_assignment.__len__(), 0)

        with self.assertRaises(RepoError) as re:
            self.__repo_assignment.update(update_assignment)
        self.assertEqual(str(re.exception), "Assignment doesn't exist")

        """
        Test for getting all assignments.
        """

        self.assertIsInstance(self.__repo_assignment.get_all_assignments(), list)

    def testGradeRepo(self):
        assignment_id = 121
        description = "maths"
        deadline = "09/04/2011"
        assignment_1 = Assignment(assignment_id, description, deadline)

        student_id = 12
        name = "Maya Jama"
        group = "Miguel group"
        student_1 = Student(student_id, name, group)

        grade_value = 7
        grade = Grade(assignment_1, student_1, grade_value)

        student = Student(12, "arthur", 913)
        self.__repo_student.add(student)
        student = Student(13, "ML Up Ea", 913)
        self.__repo_student.add(student)
        self.assertEqual(self.__repo_student.__len__(), 2)

        assignment = Assignment(12, "FP", "18/12/2021")
        self.__repo_assignment.add(assignment)
        assignment = Assignment(14, "ASC", "30/12/2021")
        self.__repo_assignment.add(assignment)
        self.assertEqual(self.__repo_assignment.__len__(), 2)

        """
        Test for adding a grade. 
        """

        self.assertEqual(self.__repo_grades.__len__(), 0)
        self.__repo_grades.add(grade)
        self.assertEqual(self.__repo_grades.__len__(), 1)

        with self.assertRaises(RepoError) as re:
            self.__repo_grades.add(grade)
        self.assertEqual(str(re.exception), "Grade already exists")

        update_grade_value = "not graded yet"
        update_grade = Grade(assignment_1, student_1, update_grade_value)

        """
        Test for updating and removing a grade. 
        """

        self.assertEqual(self.__repo_grades.__len__(), 1)
        self.__repo_grades.update(update_grade)

        assignment_id = 444
        description = "maths"
        deadline = "09/04/2011"
        assignment_2 = Assignment(assignment_id, description, deadline)

        student_id = 444
        name = "Maya Jama"
        group = "Miguel group"
        student_2 = Student(student_id, name, group)

        grade_value = 9
        bad_grade = Grade(assignment_2, student_2, grade_value)

        with self.assertRaises(RepoError) as re:
            self.__repo_grades.update(bad_grade)
        self.assertEqual(str(re.exception), "Grade doesn't exist")

        self.__repo_grades.remove(update_grade)
        self.assertEqual(self.__repo_grades.__len__(), 0)

        with self.assertRaises(RepoError) as re:
            self.__repo_grades.remove(update_grade)
        self.assertEqual(str(re.exception), "Grade doesn't exist")

        """
        Test for getting all grades. 
        """

        self.assertIsInstance(self.__repo_grades.get_all_grades(), list)

    def testStudentRepo(self):
        student_id = 12
        name = "Rick Priceless"
        group = "912"
        student = Student(student_id, name, group)

        """
        Test for adding a student.
        """

        self.assertEqual(self.__repo_student.__len__(), 0)
        self.__repo_student.add(student)
        self.assertEqual(self.__repo_student.__len__(), 1)

        new_id = 12
        new_name = "arthur"
        new_group = 913
        new_student = Student(new_id, new_name, new_group)

        with self.assertRaises(RepoError) as re:
            student = self.__repo_student.add(new_student)
        self.assertEqual(str(re.exception), "Student already exists")

        """
        Test for finding a student by ID.
        """

        self.assertTrue(self.__repo_student.find_id(12), student)

        update_id = 12
        update_name = "arthur"
        update_group = 913
        update_student = Student(update_id, update_name, update_group)

        some_id = 88

        with self.assertRaises(RepoError) as re:
            student = self.__repo_student.find_id(some_id)
        self.assertEqual(str(re.exception), "Student doesn't exist")

        """
        Test for updating and removing a student.
        """

        self.assertEqual(self.__repo_student.__len__(), 1)
        self.__repo_student.update(update_student)
        self.__repo_student.remove(update_student)
        self.assertEqual(self.__repo_student.__len__(), 0)

        update_id = 18
        update_name = "arthur"
        update_group = 913
        update_student = Student(update_id, update_name, update_group)

        with self.assertRaises(RepoError) as re:
            self.__repo_student.update(update_student)
        self.assertEqual(str(re.exception), "Student doesn't exist")

        with self.assertRaises(RepoError) as re:
            self.__repo_student.remove(update_student)
        self.assertEqual(str(re.exception), "Student doesn't exist")

        """
        Test for getting all students. 
        """

        self.assertIsInstance(self.__repo_student.get_all_students(), list)


class TestService(unittest.TestCase):

    def setUp(self):
        self.__repo_assignment = RepoAssignment()
        self.__valid_assignment = ValidAssignment()
        self.__service_assignment = ServiceAssignment(self.__repo_assignment, self.__valid_assignment)

        self.__repo_student = RepoStudent()
        self.__valid_student = ValidStudent()
        self.__service_student = ServiceStudent(self.__repo_student, self.__valid_student)

        self.__repo_grade = RepoGrade()
        self.__valid_grade = ValidGrade()
        self.__service_grade = ServiceGrade(self.__repo_grade, self.__valid_grade,
                                            self.__repo_student, self.__repo_assignment)

    def testAssignmentService(self):
        """
        Test for adding an assignment.
        """

        assignment_id = 44
        description = "physics"
        deadline = "11/09/2029"
        assignment_1 = Assignment(assignment_id, description, deadline)
        self.__service_assignment.add_assignment(assignment_id, description, deadline)

        assignment_id = 122
        description = "FP"
        deadline = "11/12/2025"
        assignment_2 = Assignment(assignment_id, description, deadline)
        self.__service_assignment.add_assignment(assignment_id, description, deadline)

        assignments = self.__service_assignment.get_assignments()
        self.assertEqual(assignments[0], assignment_1)
        self.assertEqual(assignments[1], assignment_2)

        """
        Test for removing an assignment.
        """

        assignment_id = 122
        self.__service_assignment.remove_assignment(assignment_id)
        assignments = self.__service_assignment.get_assignments()
        self.assertEqual(assignments[0], assignment_1)
        self.assertEqual(len(assignments), 1)

        """
        Test for updating an assignment.
        """

        assignment_id = 44
        new_description = "Kanye"
        new_deadline = "14/03/1999"
        new_assignment = Assignment(assignment_id, new_description, new_deadline)
        self.__service_assignment.update_assignment(assignment_id, new_description, new_deadline)
        self.assertEqual(assignments[0], new_assignment)

        """
        Test for finding an assignment by ID.
        """

        assignment_id = 44
        self.assertEqual(self.__service_assignment.find_assignment_id(assignment_id), new_assignment)

    def testGradeService(self):
        """
        Test for adding a grade.
        """
        assignment_id = 121
        description = "maths"
        deadline = "09/04/2011"
        assignment = Assignment(assignment_id, description, deadline)

        student_id = 12
        name = "Maya Jama"
        group = "Miguel group"
        student = Student(student_id, name, group)

        grade_value = 7

        self.assertEqual(self.__repo_grade.__len__(), 0)
        self.__service_grade.add_grade(assignment, student, grade_value)
        self.assertEqual(self.__repo_grade.__len__(), 1)

        """
        Test for finding a grade value by ID's.
        """

        grade_found = self.__service_grade.find_grade(assignment_id, student_id)
        self.assertEqual(grade_found, grade_value)

        """
        Test for assigning assignments.
        """

        assignment_id = 15
        description = "csgo"
        deadline = "09/04/2011"
        assignment = Assignment(assignment_id, description, deadline)
        self.__repo_assignment.add(assignment)

        student_id = 9
        name = "Dwayne Johnson"
        group = "Miguel group"
        student = Student(student_id, name, group)
        self.__repo_student.add(student)

        self.__service_grade.assign_group(assignment_id, group)
        self.assertEqual(self.__repo_grade.__len__(), 2)

        assignment_id = 21
        description = "Buddha"
        deadline = "09/04/2021"
        assignment = Assignment(assignment_id, description, deadline)
        self.__repo_assignment.add(assignment)

        student_id = 2
        name = "The Rock"
        group = "Miguel group"
        student = Student(student_id, name, group)
        self.__repo_student.add(student)

        self.__service_grade.assign_student(assignment_id, student_id)
        self.assertEqual(self.__repo_grade.__len__(), 3)

        """
        Test for grading an assignment.
        """

        new_grade = 9.95
        self.__service_grade.grade_assignment(assignment_id, student_id, new_grade)
        grade_found = self.__service_grade.find_grade(assignment_id, student_id)
        self.assertEqual(grade_found, new_grade)

        """
        Test for un-grading an assignment.
        """

        self.__service_grade.un_grade_assignment(assignment_id, student_id)
        grade_found = self.__service_grade.find_grade(assignment_id, student_id)
        self.assertEqual(grade_found, "not graded yet")

        """
        Test for removing a grade by assignment/student.
        """

        self.__service_grade.remove_assignment_grades(assignment_id)
        self.assertEqual(self.__repo_grade.__len__(), 2)
        self.__service_grade.remove_student_grades(student_id)
        self.assertEqual(self.__repo_grade.__len__(), 2)

    def testStudentService(self):
        """
        Test for adding a student.
        """
        student_id = 12
        name = "Rick Priceless"
        group = "912"
        student = Student(student_id, name, group)
        self.__service_student.add_student(student_id, name, group)

        other_student_id = 121
        other_name = "Maya Jama"
        other_group = "Miguel group"
        other_student = Student(other_student_id, other_name, other_group)
        self.__service_student.add_student(other_student_id, other_name, other_group)

        students = self.__service_student.get_students()
        self.assertEqual(students[0], student)
        self.assertEqual(students[1], other_student)

        """
        Test for removing a student.
        """

        self.__service_student.remove_student(other_student_id)
        self.assertEqual(students[0], student)
        self.assertEqual(len(self.__service_student.get_students()), 1)

        """
        Test for updating a student.
        """

        new_student = Student(student_id, other_name, other_group)
        self.__service_student.update_student(student_id, other_name, other_group)
        self.assertEqual(students[0], new_student)

        """
        Test for finding a student by ID.
        """

        self.assertEqual(self.__service_student.find_student_id(student_id), new_student)


class TestUndoRedo(unittest.TestCase):

    def setUp(self):
        self.__repo_assignments = RepoAssignment()
        self.__repo_grades = RepoGrade()
        self.__repo_students = RepoStudent()

        self.__valid_assignment = ValidAssignment()
        self.__valid_grade = ValidGrade()
        self.__valid_student = ValidStudent()

        self.__service_assignment = ServiceAssignment(self.__repo_assignments, self.__valid_assignment)
        self.__service_grade = ServiceGrade(self.__repo_grades, self.__valid_grade,
                                            self.__repo_students, self.__repo_assignments)
        self.__service_student = ServiceStudent(self.__repo_students, self.__valid_student)

        self.__undo_redo = UndoRedo(self.__service_assignment, self.__service_grade, self.__service_student)

    def testAssignmentUndoRedo(self):
        assignment_id = 44
        description = "physics"
        deadline = "11/09/2029"
        assignment = Assignment(assignment_id, description, deadline)

        """
        Undo/Redo add test.
        """

        self.__service_assignment.add_assignment(assignment_id, description, deadline)

        self.__undo_redo.add_to_undo_list("add a", assignment)
        self.__undo_redo.add_to_redo_list("add a", assignment)

        assignments = self.__repo_assignments.get_all_assignments()
        self.assertEqual(len(assignments), 1)

        self.__undo_redo.service_undo()
        assignments = self.__repo_assignments.get_all_assignments()
        self.assertEqual(len(assignments), 0)

        self.__undo_redo.service_redo()
        assignments = self.__repo_assignments.get_all_assignments()
        self.assertEqual(len(assignments), 1)

        """
        Undo/Redo remove test.
        """

        self.__service_assignment.remove_assignment(assignment_id)
        assignments = self.__repo_assignments.get_all_assignments()
        self.assertEqual(len(assignments), 0)

        self.__undo_redo.add_to_undo_list("del a", assignment)
        self.__undo_redo.add_to_redo_list("del a", assignment)

        self.__undo_redo.service_undo()
        assignments = self.__repo_assignments.get_all_assignments()
        self.assertEqual(len(assignments), 1)

        """
        Undo/Redo update test.
        """

        new_description = "ASC"
        new_deadline = "12/10/1999"
        self.__service_assignment.update_assignment(assignment_id, new_description, new_deadline)

        self.__undo_redo.add_to_undo_list("up a", assignment)
        self.__undo_redo.add_to_redo_list("up a", assignment)

        self.__undo_redo.service_undo()

        old_description = assignment.get_description()
        old_deadline = assignment.get_deadline()
        self.assertEqual(old_description, description)
        self.assertEqual(old_deadline, deadline)

    def testGradeUndoRedo(self):
        assignment_id = 121
        description = "maths"
        deadline = "09/04/2011"
        assignment = Assignment(assignment_id, description, deadline)
        self.__repo_assignments.add(assignment)

        student_id = 12
        name = "Maya Jama"
        group = "Miguel group"
        student = Student(student_id, name, group)
        self.__repo_students.add(student)

        student_id = 14
        name = "Michael"
        group = "Miguel group"
        student_1 = Student(student_id, name, group)
        self.__repo_students.add(student_1)

        """
        Undo/Redo assign group.
        """

        self.__service_grade.assign_group(assignment_id, group)
        self.assertEqual(self.__repo_grades.__len__(), 2)

        self.__undo_redo.add_to_undo_list("as g", (assignment_id, group))
        self.__undo_redo.add_to_redo_list("as g", (assignment_id, group))

        self.__undo_redo.service_undo()
        self.assertEqual(self.__repo_grades.__len__(), 0)

        self.__undo_redo.service_redo()
        self.assertEqual(self.__repo_grades.__len__(), 2)

        self.__undo_redo.service_undo()
        self.assertEqual(self.__repo_grades.__len__(), 0)

        """
        Undo/Redo assign student.
        """

        self.__service_grade.assign_student(assignment_id, student_id)
        self.assertEqual(self.__repo_grades.__len__(), 1)

        self.__undo_redo.add_to_undo_list("as s", (assignment_id, student_id))
        self.__undo_redo.add_to_redo_list("as s", (assignment_id, student_id))

        self.__undo_redo.service_undo()
        self.assertEqual(self.__repo_grades.__len__(), 0)

        self.__undo_redo.service_redo()
        self.assertEqual(self.__repo_grades.__len__(), 1)

        """
        Undo/Redo grade assignment.
        """

        new_grade = 8.5
        self.__service_grade.grade_assignment(assignment_id, student_id, new_grade)
        grade_found = self.__service_grade.find_grade(assignment_id, student_id)
        self.assertEqual(grade_found, new_grade)

        self.__undo_redo.add_to_undo_list("up g", (assignment_id, student_id))
        self.__undo_redo.add_to_redo_list("up g", (assignment_id, student_id, new_grade))

        self.__undo_redo.service_undo()
        grade_found = self.__service_grade.find_grade(assignment_id, student_id)
        self.assertEqual(grade_found, "not graded yet")

        """

        """

    def testStudentUndoRedo(self):
        student_id = 12
        name = "Rick Priceless"
        group = "912"
        student = Student(student_id, name, group)

        """
        Undo/Redo add test.
        """

        self.__service_student.add_student(student_id, name, group)

        self.__undo_redo.add_to_undo_list("add s", student)
        self.__undo_redo.add_to_redo_list("add s", student)

        students = self.__repo_students.get_all_students()
        self.assertEqual(len(students), 1)

        self.__undo_redo.service_undo()
        students = self.__repo_students.get_all_students()
        self.assertEqual(len(students), 0)

        self.__undo_redo.service_redo()
        students = self.__repo_students.get_all_students()
        self.assertEqual(len(students), 1)

        """
        Undo/Redo remove test.
        """

        self.__service_student.remove_student(student_id)
        students = self.__repo_students.get_all_students()
        self.assertEqual(len(students), 0)

        self.__undo_redo.add_to_undo_list("del s", student)
        self.__undo_redo.add_to_redo_list("del s", student)

        self.__undo_redo.service_undo()
        students = self.__repo_students.get_all_students()
        self.assertEqual(len(students), 1)

        """
        Undo/Redo update test.
        """

        new_name = "Messi"
        new_group = "7"
        self.__service_student.update_student(student_id, new_name, new_group)

        self.__undo_redo.add_to_undo_list("up s", student)
        self.__undo_redo.add_to_redo_list("up s", student)

        self.__undo_redo.service_undo()

        old_name = student.get_name()
        old_group = student.get_group()
        self.assertEqual(old_name, name)
        self.assertEqual(old_group, group)


if __name__ == '__main__':
    unittest.main()

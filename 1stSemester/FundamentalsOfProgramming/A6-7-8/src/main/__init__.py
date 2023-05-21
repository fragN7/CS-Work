"""
Created by @AlenMichael
Nov 2021
"""


from src.repository.Assignment import RepoAssignment
from src.repository.Grade import RepoGrade
from src.repository.Student import RepoStudent

from src.validation.Assignment import ValidAssignment
from src.validation.Grade import ValidGrade
from src.validation.Student import ValidStudent

from src.services.Assignment import ServiceAssignment
from src.services.Grade import ServiceGrade
from src.services.Student import ServiceStudent
from src.services.Population import Population
from src.services.UndoRedo import UndoRedo

from src.ui.UsInterface import UserInterface


if __name__ == '__main__':
    valid_student = ValidStudent()
    valid_assignment = ValidAssignment()
    valid_grade = ValidGrade()

    repo_student = RepoStudent()
    repo_grade = RepoGrade()
    repo_assignment = RepoAssignment()

    service_grade = ServiceGrade(repo_grade, valid_grade, repo_student, repo_assignment)
    service_assignment = ServiceAssignment(repo_assignment, valid_assignment)
    service_student = ServiceStudent(repo_student, valid_student)

    service_population = Population(service_assignment, service_student, service_grade)

    undo_redo = UndoRedo(service_assignment, service_grade, service_student)
    ui = UserInterface(service_student, service_assignment, service_grade, service_population, undo_redo)
    ui.run_ui()

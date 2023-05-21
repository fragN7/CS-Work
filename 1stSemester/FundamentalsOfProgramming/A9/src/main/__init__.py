"""
Created by @AlenMichael
Nov 2021
"""


from src.repository.Assignment import RepoAssignment
from src.repository.Grade import RepoGrade
from src.repository.Student import RepoStudent

from src.repository.AssignmentPickle import PickleAssignment
from src.repository.GradePickle import PickleGrade
from src.repository.StudentPickle import PickleStudent

from src.repository.AssignmentText import TextAssignment
from src.repository.GradeText import TextGrade
from src.repository.StudentText import TextStudent

from src.validation.Assignment import ValidAssignment
from src.validation.Grade import ValidGrade
from src.validation.Student import ValidStudent

from src.services.Assignment import ServiceAssignment
from src.services.Grade import ServiceGrade
from src.services.Student import ServiceStudent
from src.services.Population import Population
from src.services.UndoRedo import UndoRedo

from src.ui.UsInterface import UserInterface
from src.main.settings import Settings


if __name__ == '__main__':
    settings = Settings("properties")
    config = settings.config_settings()
    inmemory = False
    ok = True
    if not config:
        ok = False
    elif config[0] == "inmemory":
        repo_student = RepoStudent()
        repo_grade = RepoGrade()
        repo_assignment = RepoAssignment()
        inmemory = True
    elif config[0] == "textfiles":
        repo_student = TextStudent(config[1])
        repo_assignment = TextAssignment(config[2])
        repo_grade = TextGrade(config[3], repo_student, repo_assignment)
    else:
        repo_student = PickleStudent(config[1])
        repo_assignment = PickleAssignment(config[2])
        repo_grade = PickleGrade(config[3])

    if ok:
        valid_student = ValidStudent()
        valid_assignment = ValidAssignment()
        valid_grade = ValidGrade()

        service_grade = ServiceGrade(repo_grade, valid_grade, repo_student, repo_assignment)
        service_assignment = ServiceAssignment(repo_assignment, valid_assignment)
        service_student = ServiceStudent(repo_student, valid_student)
        undo_redo = UndoRedo(service_assignment, service_grade, service_student)

        if inmemory:
            service_population = Population(service_assignment, service_student, service_grade)
            service_population.populate_list()

        ui = UserInterface(service_student, service_assignment, service_grade, undo_redo)
        ui.run_ui()

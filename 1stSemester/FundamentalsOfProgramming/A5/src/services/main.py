
"""
Created by @AlenMichael
November 2021
"""

from src.ui.ui import UserInterface
from src.services.services import ServiceExpense
from src.repository.repo import RepoExpense, RepoTextExpense
from src.valid.validator import ValidateExpense
from src.testing.tests import Test

if __name__ == '__main__':
    validator_expense = ValidateExpense()
    repo_expense = RepoTextExpense("expense.txt")
    service_expense = ServiceExpense(repo_expense, validator_expense)
    user_interface = UserInterface(service_expense)

    test = Test()
    test.run_all_tests()

    ui = UserInterface(service_expense)
    ui.run_ui()



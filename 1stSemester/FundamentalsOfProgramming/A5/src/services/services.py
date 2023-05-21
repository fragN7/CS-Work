from src.domain.expense import Expense
import random


class ServiceExpense(object):

    def __init__(self, repo_expenses, validator_expense):
        self.__repo_expenses = repo_expenses
        self.__validator_expense = validator_expense

    def num_expenses(self):
        return len(self.__repo_expenses)

    def add_expense(self, day, amount, typ):
        expense = Expense(day, amount, typ)
        self.__validator_expense.validate(expense)
        self.__repo_expenses.add_expense(expense)
        self.__repo_expenses.add_to_undo_list()

    def get_expenses(self):
        return self.__repo_expenses.get_expenses()

    def remove_expense(self, expense):
        self.__repo_expenses.remove_expense(expense)

    def filter_expenses(self, value):
        ok = 0
        for i in self.get_expenses():
            if Expense.get_amount(i) < value:
                self.remove_expense(i)
                ok = 1
        if ok:
            self.__repo_expenses.add_to_undo_list()

    def undo_expense(self):
        self.__repo_expenses.add_to_new_list()
        self.__repo_expenses.delete_undo_list()

    def populate_expenses(self):
        types = ["wife", "kids", "mom", "dad", "brother", "sister"]
        for i in range(10):
            day = random.randint(1, 30)
            amount = random.randint(0, 1000)
            typ = random.choice(types)
            self.add_expense(day, amount, typ)

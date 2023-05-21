from src.domain.expense import Expense
from src.valid.validator import ValidateExpense
from src.errors.exception import ValidationError
from src.repository.repo import RepoExpense
from src.services.services import ServiceExpense


class Test:

    def __run_create_expense_test(self):
        day = 16
        amount = 1200
        typ = "ps4"
        expense = Expense(day, amount, typ)
        assert (expense.get_day() == day)
        assert (expense.get_amount() == amount)
        assert (expense.get_typ() == typ)

        amount1 = 1400
        other = Expense(day, amount1, typ)
        assert(Expense.__eq__(expense, other))
        assert(Expense.__str__(other) == "On day 16 you spent 1400 on ps4")

    def __run_validate_expense_test(self):
        day = 16
        amount = 1200
        typ = "ps4"
        expense = Expense(day, amount, typ)
        valid = ValidateExpense()
        valid.validate(expense)

        invalid_day = 31
        invalid_amount = -14
        invalid_typ = ""
        expense_invalid = Expense(invalid_day, amount, typ)
        try:
            valid.validate(expense_invalid)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "Invalid day\n")

        expense_invalid = Expense(invalid_day, invalid_amount, invalid_typ)
        try:
            valid.validate(expense_invalid)
            assert False
        except ValidationError as ve:
            assert(str(ve) == "Invalid day\nInvalid amount\nInvalid type")

    def __run_add_repo_expense_test(self):
        day = 16
        amount = 1200
        typ = "ps4"
        expense = Expense(day, amount, typ)
        repo = RepoExpense()
        assert (repo.__len__() == 0)
        repo.add_expense(expense)
        assert (repo.__len__() == 1)

    def __run_add_service_test(self):
        day = 16
        amount = 1200
        typ = "ps4"
        valid = ValidateExpense()
        repo = RepoExpense()
        service = ServiceExpense(repo, valid)
        assert (service.num_expenses() == 0)
        service.add_expense(day, amount, typ)
        assert (service.num_expenses() == 1)

    def __run_filter_service_test(self):
        day = 16
        amount = 1200
        typ = "ps4"
        value = 750
        valid = ValidateExpense()
        repo = RepoExpense()
        service = ServiceExpense(repo, valid)
        service.add_expense(day, amount, typ)
        service.add_expense(day, 450, typ)
        service.add_expense(day, 699, typ)
        assert (service.num_expenses() == 3)
        service.filter_expenses(value)
        assert (service.num_expenses() == 1)

    def run_all_tests(self):
        self.__run_create_expense_test()
        self.__run_validate_expense_test()
        self.__run_add_repo_expense_test()
        self.__run_add_service_test()
        self.__run_filter_service_test()

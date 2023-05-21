from src.errors.exception import ValidationError


class bcolors:
    RED = '\033[31m'
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


class UserInterface:

    def __init__(self, service_expense):
        self.__service_expense = service_expense

    def __cmd_menu(self):
        print(bcolors.WARNING + "List of commands for your expenses ->\n" + bcolors.ENDC)
        print(bcolors.CYAN + "Add" + bcolors.ENDC)
        print(bcolors.CYAN + "List" + bcolors.ENDC)
        print(bcolors.CYAN + "Filter" + bcolors.ENDC)
        print(bcolors.CYAN + "Undo" + bcolors.ENDC)
        print(bcolors.CYAN + "Exit\n" + bcolors.ENDC)

    def __ui_add_expense(self):
        day = input(bcolors.GREEN + "Day: " + bcolors.ENDC)
        amount = input(bcolors.GREEN + "Amount: " + bcolors.ENDC)
        typ = input(bcolors.GREEN + "Type: " + bcolors.ENDC)
        try:
            day = int(day)
        except ValueError:
            print(bcolors.WARNING + "Invalid day" + bcolors.ENDC)
            return
        try:
            amount = int(amount)
        except ValueError:
            print(bcolors.WARNING + "Invalid amount" + bcolors.ENDC)
            return
        self.__service_expense.add_expense(day, amount, typ)

    def __ui_list_expense(self):
        number_expenses = self.__service_expense.num_expenses()
        if number_expenses == 0:
            print(bcolors.WARNING + "List of expenses is empty" + bcolors.ENDC)
            return
        all_expenses = self.__service_expense.get_expenses()
        for i in all_expenses:
            print(i)

    def __ui_filter_expense(self):
        value = input(bcolors.GREEN + "Value: " + bcolors.ENDC)
        try:
            value = int(value)
        except ValueError:
            print(bcolors.WARNING + "Invalid value" + bcolors.ENDC)
            return
        self.__service_expense.filter_expenses(value)

    def __ui_undo_expense(self):
        try:
            self.__service_expense.undo_expense()
        except IndexError:
            print(bcolors.WARNING + "Can not undo anymore" + bcolors.ENDC)

    def run_ui(self):
        self.__cmd_menu()
        self.__service_expense.populate_expenses()
        while True:
            cmd = input(bcolors.BLUE + "Please write your command here: " + bcolors.ENDC)
            cmd = cmd.lower()
            if cmd == "exit":
                return None
            elif cmd == "":
                continue
            elif cmd == "add":
                try:
                    self.__ui_add_expense()
                except ValidationError as ve:
                    print(bcolors.WARNING + "Validation error: \n" + str(ve) + bcolors.ENDC)
            elif cmd == "list":
                self.__ui_list_expense()
            elif cmd == "filter":
                self.__ui_filter_expense()
            elif cmd == "undo":
                self.__ui_undo_expense()
            else:
                print(bcolors.WARNING + "Invalid command!" + bcolors.ENDC)

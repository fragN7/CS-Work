"""
  User interface module
"""
from functions import split_command, get_action, pop_list
from functions import add_insert, list_transactions, remove_transaction, replace_transaction
from functions import sum_transaction, max_transaction, filter_transaction, undo_transaction


def print_cmd_menu():
    print("Bank Account:\n")
    print("Here is a list of all possible commands:")
    print("-------------------------------------------------\n")
    print("        Insert <day> <value> <type> <description>")
    print("        Add <value> <type> <description>")
    print("        Remove <day>")
    print("        Remove <start day> to <end day>")
    print("        Remove <type>")
    print("        Replace <day> <type> <description> with <value>")
    print("        List")
    print("        List <type>")
    print("        List [ < | = | > ] <value>")
    print("        List balance <day>")
    print("        Sum <type>")
    print("        Max <type> <value>")
    print("        Filter <type>")
    print("        Filter <type> <value>")
    print("        Undo")
    print("        Exit\n")
    print("---------------------------------------------------")


def run_ui():
    l = []
    undo_list = []
    print_cmd_menu()
    pop_list(l, undo_list)
    undo_list.clear()
    commands = ["add", "insert", "list", "remove", "replace", "sum", "max", "filter", "undo"]
    while True:
        cmd = input("Please write your command here ->")
        cmd = split_command(cmd)
        action = get_action(cmd)
        if action == "exit" and len(cmd) == 1:
            return None
        if action == "add" or action == "insert":
            add_insert(cmd, l, undo_list)
        if action == "list":
            list_transactions(cmd, l)
        if action == "remove":
            remove_transaction(cmd, l, undo_list)
        if action == "replace":
            replace_transaction(cmd, l, undo_list)
        if action == "sum":
            sum_transaction(cmd, l)
        if action == "max":
            max_transaction(cmd, l)
        if action == "filter":
            filter_transaction(cmd, l, undo_list)
        if action == "undo":
            undo_transaction(cmd, l, undo_list)
        if action not in commands:
            print("Invalid command")

"""
  Program functionalities module
"""
import datetime
import random


def undo_transaction(cmd, l, undo_list):
    try:
        undo = verify_undo_transaction(cmd, undo_list)
        if undo[-1][0] == "insert":
            l.remove(undo[-1][1])
            undo_list.pop(-1)
        elif undo[-1][0] == "replace":
            for i in l:
                if get_day(i) == get_day(undo[-1][1]) and get_type(i) == get_type(undo[-1][1]) and get_desc(i) == get_desc(undo[-1][1]):
                    i["value"] = undo[-1][2]
            undo_list.pop(-1)
        elif undo[-1][0] == "remove":
            if undo[-1][2] > 1:
                y = undo[-1][2]
                for i in range(y):
                    l.append(undo[-1][1])
                    undo_list.pop(-1)
    except TypeError:
        print("Invalid 'undo' command")
    except ValueError:
        print("Invalid 'undo' command")
    except IndexError:
        print("Can not undo anymore")


def verify_undo_transaction(cmd, undo_list):
    if len(cmd) != 1:
        raise ValueError("Invalid command")
    try:
        return undo_list
    except IndexError:
        print("Can not undo anymore")


def filter_transaction(cmd, l, undo_list):
    try:
        x = verify_filter_transaction(cmd)
        if isinstance(x, tuple):
            if x[0] == "in":
                cmd = ["remove", "out"]
                remove_transaction(cmd, l, undo_list)
                if undo_list[-1][1]["type"] != undo_list[-2][1]["type"]:
                    y = 1
                else:
                    y = undo_list[-1][-1] + 1
                    for i in l:
                        if get_value(i) >= x[1] and get_type(i) == "in":
                             l.remove(i)
                             undo_list.append(["remove", i, y])
                             y = y + 1
            else:
                cmd = ["remove", "in"]
                remove_transaction(cmd, l, undo_list)
                if undo_list[-1][1]["type"] != undo_list[-2][1]["type"]:
                    y = 1
                else:
                    y = undo_list[-1][-1] + 1
                    for i in l:
                        if get_value(i) >= x[1] and get_type(i) == "out":
                            l.remove(i)
                            undo_list.append(["remove", i, y])
                            y = y + 1
        else:
             if x == "in":
                cmd = ["remove", "out"]
                remove_transaction(cmd, l, undo_list)
             else:
                cmd = ["remove", "in"]
                remove_transaction(cmd, l, undo_list)
    except ValueError:
        print("Invalid 'list' command")


def verify_filter_transaction(cmd):
    if len(cmd) != 2 and len(cmd) != 3:
        raise ValueError("Invalid command")
    if len(cmd) == 2:
        if cmd[1] == "in" or cmd[1] == "out":
            return cmd[1]
        else:
            raise ValueError("Invalid command")
    else:
        if cmd[1] == "in" or cmd[1] == "out":
            return cmd[1], int(cmd[2])
        else:
            raise ValueError("Invalid command")


def max_transaction(cmd, l):
    try:
        x = verify_max_transaction(cmd)
        if x[0] == "in":
            max = int(0)
            for i in l:
                if x[1] == get_day(i):
                    if get_value(i) > max:
                        max = get_value(i)
            print(f"Max value of all {x[0]} from day {x[1]} transactions is {max}")
        else:
            max = int(0)
            for i in l:
                if x[1] == get_day(i):
                    if get_value(i) > max:
                        max = get_value(i)
            print(f"Max value of all {x[0]} from day {x[1]} transactions is {max}")
    except ValueError:
        print("Invalid command")


def verify_max_transaction(cmd):
    if len(cmd) != 3:
        raise ValueError("Invalid 'max' command")
    if cmd[1] == "in" or cmd[1] == "out":
        return cmd[1], int(cmd[2])
    else:
        raise ValueError("Invalid 'sum' command")


def sum_transaction(cmd, l):
    try:
        x = verify_sum_transaction(cmd)
        if x == "in":
            s = int(0)
            for i in l:
                if get_type(i) == "in":
                    s = s + get_value(i)
        else:
            s = int(0)
            for i in l:
                if get_type(i) == "out":
                    s = s + get_value(i)
        print(f"Sum of all {x} transactions is {s}")
    except ValueError:
        print("Invalid command")


def verify_sum_transaction(cmd):
    if len(cmd) != 2:
        raise ValueError("Invalid 'sum' command")
    if cmd[1] == "in" or cmd[1] == "out":
        return cmd[1]
    else:
        raise ValueError("Invalid 'sum' command")


def replace_transaction(transaction, l, undo_list):
    try:
        transaction = verify_replace_transaction(transaction)
        for i in l:
            if get_day(i) == get_day(transaction) and get_type(i) == get_type(transaction) and get_desc(i) == get_desc(transaction):
                x = int(get_value(i))
                i["value"] = transaction["value"]
        undo_list.append(["replace", transaction, x])
    except ValueError:
        print("Invalid command")
    except UnboundLocalError:
        print("Invalid command")


def verify_replace_transaction(cmd):
    if len(cmd) != 6:
        raise ValueError('Invalid command')
    if cmd[4] != "with":
        raise ValueError('Invalid command')
    if cmd[2] != "in" and cmd[2] != "out":
        raise ValueError('Invalid command')
    day = int(cmd[1])
    type = cmd[2]
    desc = cmd[3]
    value = int(cmd[5])
    return {
        "day": day,
        "value": value,
        "type": type,
        "description": desc
    }


def remove_transaction(cmd, l, undo_list):
    out = []
    x = int(0)
    try:
        cmd = verify_remove_transaction(cmd)
        if isinstance(cmd, tuple):
            for i in l:
                if cmd[0] <= get_day(i) <= cmd[1]:
                    x = x + 1
                    out.append(i)
                    undo_list.append(["remove", i, x])
        else:
            if isinstance(cmd, int):
                for i in l:
                    if get_day(i) == cmd:
                        x = x + 1
                        out.append(i)
                        undo_list.append(["remove", i, x])
            else:
                for i in l:
                    if get_type(i) == cmd:
                        x = x + 1
                        out.append(i)
                        undo_list.append(["remove", i, x])
    except ValueError:
        print("Invalid command")
    new_l = [x for x in l if x not in out]
    l.clear()
    l.extend(new_l)


def verify_remove_transaction(cmd):
    if len(cmd) != 2 and len(cmd) != 4:
        raise ValueError("Invalid command")
    if "to" in cmd:
        return int(cmd[1]), int(cmd[3])
    else:
        if cmd[1] == "in" or cmd[1] == "out":
            return cmd[1]
        else:
            return int(cmd[1])


def list_transactions(cmd, l):
    if len(cmd) == 1:
        for i in l:
            print(i)
    else:
        try:
            x = verify_list_transactions(cmd)
            if isinstance(x, tuple):
                if x[0].lower() == "balance":
                    s = int(0)
                    for i in l:
                        if get_day(i) == x[1]:
                            if get_type(i) == "in":
                                s = s + get_value(i)
                            else:
                                s = s - get_value(i)
                    print(f"Balance at the end of the day {x[1]} is {s}")
                if x[0] == ">":
                    for i in l:
                        if get_value(i) > x[1]:
                            print(i)
                if x[0] == "<":
                    for i in l:
                        if get_value(i) < x[1]:
                            print(i)
                if x[0] == "=":
                    for i in l:
                        if get_value(i) == x[1]:
                            print(i)
                if x[0] != "=" and x[0] != "<" and x[0] != ">" and x[0] != "balance":
                    raise ValueError("Invalid command")
            else:
                for i in l:
                    if get_type(i) == x:
                        print(i)
        except ValueError:
            print("Invalid 'list' command")


def verify_list_transactions(cmd):
    if cmd[1] == "in" or cmd[1] == "out":
        return cmd[1]
    if len(cmd) != 3:
        raise ValueError("Invalid command")
    else:
        return cmd[1], int(cmd[2])


def add_insert(cmd, l, undo_list):
    try:
        transaction = verify_add_insert(cmd)
        if transaction not in l and transaction is not None:
             l.append(transaction)
             undo_list.append(["insert", transaction, 0])
        elif transaction in l:
            print("Transaction already in list")
    except ValueError:
        print("Can not add/insert transaction")


def verify_add_insert(cmd):
    if len(cmd) != 4 and len(cmd) != 5:
        raise ValueError('Invalid command')
    if len(cmd) == 4 and cmd[0] == "add":
        day = datetime.datetime.now().strftime("%d")
        value = cmd[1]
        type = cmd[2]
        description = cmd[3]
        transaction = create_transaction(day, value, type, description)
        try:
            transaction = validate_transaction(transaction)
            return transaction
        except ValueError:
            print("Invalid 'add/insert' transaction")
    elif len(cmd) == 5 and cmd[0] == "insert":
        day = cmd[1]
        value = cmd[2]
        type = cmd[3]
        description = cmd[4]
        transaction = create_transaction(day, value, type, description)
        try:
            transaction = validate_transaction(transaction)
            return transaction
        except ValueError:
            print("Invalid 'add/insert' transaction")
    else:
        print("Invalid command")


def split_command(cmd):
    return cmd.split()


def get_action(cmd):
    return cmd[0].lower()


def get_day(transaction):
    return transaction["day"]


def get_value(transaction):
    return transaction["value"]


def get_type(transaction):
    return transaction["type"]


def get_desc(transaction):
    return transaction["description"]


def pop_list(l, undo_list):
    types = ["in", "out"]
    descriptions = ["wife", "kids", "mom", "dad", "brother", "sister"]
    for i in range(10):
        cmd = str("insert " + str(random.randint(1, 30)) + " " + str(random.randint(0, 1000)) + " " + str(random.choice(types)) + " " + str(random.choice(descriptions)))
        cmd = split_command(cmd)
        add_insert(cmd, l, undo_list)


def validate_transaction(transaction):

    try:
        x = get_day(transaction)
        x = int(x)
    except ValueError:
        print('Invalid day')
    if x not in range(1, 31) and type(x) != "int":
        raise ValueError('Day not in month')
    try:
        y = get_value(transaction)
        y = int(y)
    except ValueError:
        print('Invalid value')
    if get_type(transaction) != "in" and get_type(transaction) != "out":
        raise ValueError('Invalid type')
    transaction = create_transaction(x, y, get_type(transaction), str(get_desc(transaction)))
    return transaction


def create_transaction(day, value, type, description):
    return {
        'day': day,
        'value': value,
        'type': type,
        'description': description
    }
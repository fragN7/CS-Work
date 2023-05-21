import datetime
import random

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
    print("        Exit")
    print("---------------------------------------------------")

def create_transaction(day=None,value=None,type=None,desc=""):
    """
    :param day: day of transaction,None by default
    :param value: value of transaction
    :param type: type of transaction (in or out)
    :param descr: description of transaction
    :return: dictionary represented as a transaction
    """
    if value is None:
        raise ValueError('Invalid value')
    if type is None or (type!="in" and type!="out"):
        raise ValueError('Invalid type')
    if day is None:
        day=(datetime.datetime.now().strftime("%d"))

    return {
    'day':day,
    'value':value,
    'type':type,
    'description':desc
    }

def get_day(bank):
    return bank["day"]

def get_value(bank):
    return bank["value"]

def get_type(bank):
    return bank["type"]

def get_desc(bank):
    return bank["description"]

def verify_remove(trl):
    """
    :param trl: Command, eventually turns in a tuple/int if the tuple/int is (correct)
    :param l: List of transactions
    """
    if "to" in trl:
        return int(trl[1]),int(trl[3])
    else:
        if trl[1]=="in" or trl[1]=="out":
            return trl[1]
        else:
            return int(trl[1])

def remove_transaction(trl,l):
    """
    :param trl: Command, eventually turns in a tuple/int if the tuple/int is (correct)
    :param l: List of transactions
    """
    out=[]
    try:
        trl=verify_remove(trl)
        if isinstance(trl,tuple):
            for i in l:
                if trl[0] <= get_day(i) <= trl[1]:
                    out.append(i)
        else:
            if isinstance(trl,int):
                for i in l:
                    if get_day(i)== trl:
                        out.append(i)
            else:
                for i in l:
                    if get_type(i)==trl:
                        out.append(i)
    except ValueError:
        print("Incvalid command")
    new_l=[x for x in l if x not in out]
    l.clear()
    l.extend(new_l)

def verify_replace(trl):
    """
    :param trl: Command as a list
    :return: Dictionary with the replaced values
    """
    if len(trl)!=6:
        raise ValueError('Invalid command')
    if trl[4]!="with":
        raise ValueError('Invalid command')
    if trl[2]!="in" and trl[2]!="out":
        raise ValueError('Invalid command')
    day=int(trl[1])
    type=trl[2]
    desc=trl[3]
    value=int(trl[5])
    return {
        "day": day,
        "value": value,
        "type": type,
        "description": desc
    }

def replace_transaction(trl,l):
    """
    :param trl: Commands, eventually turns in a dictionary if the dictionary is (correct)
    :param l: List of transactions
    """
    try:
        trl=verify_replace(trl)
        for i in l:
            if get_day(i)==get_day(trl) and get_type(i)==get_type(trl) and get_desc(i)==get_desc(trl):
                i["value"] = trl["value"]
    except ValueError:
        print("Invalid command")

def verify_add_insert(trl):
    """
    :param trl: Command as a list
    :return: Dictionary with the values
    """
    if len(trl)!=4 and len(trl)!=5:
        raise ValueError('Invalid command')
    else:
        if len(trl)>4:
            try:
                day=int(trl[1])
            except ValueError:
                print("Invalid type of day")
        else:
            day=None
        if len(trl)>4:
            try:
                value = int(trl[2])
            except ValueError:
                print("Invalid type of value")
        else:
            try:
                value = int(trl[1])
            except ValueError:
                print("Invalid type of value")
        if len(trl)>4:
            type=trl[3]
        else:
            type=trl[2]
        if len(trl)>4:
            desc=trl[4]
        else:
            desc=trl[3]
    return {
        'day': day,
        'value': value,
        'type': type,
        'description': desc
    }

def add_insert(trl,l):
    """
    :param trl: Dictionary of transaction
    :param l: List of transactions
    """
    try:
        x=verify_add_insert(trl)
        l.append(create_transaction(x["day"], x["value"], x["type"], str(x["description"])))
    except ValueError:
        print("Invalid transaction")

def verify_list(trl):
    if trl[1]=="in" or trl[1]=="out":
            return trl[1]
    if len(trl)!=3:
        raise ValueError("Invalid command")
    else:
        return trl[1],int(trl[2])

def list_transaction(trl,l):
    """
    :param trl:Command as a list
    :param l:List of transactions
    """
    if len(trl)==1:
        for i in l:
            print(i)
    else:
        try:
            trl=verify_list(trl)
            if isinstance(trl,tuple):
                    if trl[0].lower()=="balance":
                        s=int(0)
                        for i in l:
                            if get_day(i)<=trl[1]:
                                if get_type(i)=="in":
                                     s=s+get_value(i)
                                else:
                                     s=s-get_value(i)
                        print(f"Balance at the end of the day {trl[1]} is {s}")
                    if trl[0]==">":
                        for i in l:
                            if get_value(i)>trl[1]:
                                print(i)
                    if trl[0] == "<":
                        for i in l:
                            if get_value(i)<trl[1]:
                                print(i)
                    if trl[0]=="=":
                        for i in l:
                            if get_value(i)==trl[1]:
                                print(i)
            else:
                for i in l:
                    if get_type(i)==trl:
                        print(i)
        except ValueError:
            print("Invalid command")

def verify_cmd(cmd,l):
    """
    :param cmd: Command as a list
    :param l: List of transactions
    """
    cmd=split_command(cmd)
    action=str(cmd[0]).lower()
    if action == "add" or action=="insert":
        add_insert(cmd,l)
    if action == "remove":
        remove_transaction(cmd, l)
    if action=="replace":
        replace_transaction(cmd,l)
    if action=="list":
        list_transaction(cmd,l)
    if action != "add" and action != "insert" and action != "remove" and action != "replace" and action != "list":
        print("Invalid command")

def split_command(cmd):
    """
    :param cmd: Command, type string
    :return: List, containing all strings that are separated by spaces
    """
    cmd = cmd.split()
    return cmd

def insert_pop(trl,l):
    """
    Added separate function for adding the already populated transactions, because it is
    """
    cmd=split_command(trl)
    add_insert(cmd,l)

def pop_list(l):
    """
    :param l: The list of random transations
    """
    types=["in","out"]
    desc=["wife","kids","mom","dad","brother","sister"]
    for x in range(10):
        insert_pop("insert " + str(random.randint(1, 30)) + " " + str(random.randint(0, 1000)) + " " + str(random.choice(types)) + " " + str(random.choice(desc)),l)

def run_start():
    print_cmd_menu()
    bank_list=[]
    pop_list(bank_list)
    while True:
        cmd=input("Please write your command here:")
        x=[i.strip() for i in cmd.split(' ')]
        if x[0].lower()=="exit":
            return None
        verify_cmd(cmd,bank_list)

def test_splitcmd():
    assert split_command("add 12 in butter")==["add","12","in","butter"]
    assert split_command("replace    20    out sister with   0")==["replace","20","out","sister","with","0"]
    assert split_command("remove in")==["remove","in"]

def test_getters():
    x={'day':24,'value':1201,'type':"in",'description':"kids"}
    assert get_day(x)==24
    assert get_value(x)==1201
    assert get_type(x)=="in"
    assert get_desc(x)=="kids"
    try:
        assert get_type(x)=="out"
    except AssertionError:
        print("")

def run_tests():
    test_splitcmd()
    test_getters()

run_start()
run_tests()
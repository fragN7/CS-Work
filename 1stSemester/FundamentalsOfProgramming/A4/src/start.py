"""
  Start the program by running this module
"""
from functions import *
from ui import *


def test_verify_undo_transaction():
    cmd = "undo"
    cmd = split_command(cmd)
    u = ["remove", {'day': 12, 'value': 1200, 'type': "in", 'description': "life"}, 1]
    assert verify_undo_transaction(cmd, u) == u


def test_verify_filter_transaction():
    cmd = "filter in"
    cmd = split_command(cmd)
    assert verify_filter_transaction(cmd) == "in"

    cmd1 = "filter in 1200"
    cmd1 = split_command(cmd1)
    assert verify_filter_transaction(cmd1)[0] == "in"
    assert verify_filter_transaction(cmd1)[1] == 1200

    cmd2 = "filter in damn"
    cmd2 = split_command(cmd2)
    try:
        x = verify_filter_transaction(cmd2)
    except ValueError:
        return None


def test_verify_max_transaction():
    cmd = "max in 15"
    cmd = split_command(cmd)
    assert verify_max_transaction(cmd)[0] == "in"
    assert verify_max_transaction(cmd)[1] == 15

    cmd1 = "max out life"
    cmd1 = split_command(cmd1)
    try:
        x = verify_max_transaction(cmd1)
    except ValueError:
        return None


def test_verify_sum_transaction():
    cmd = "sum in"
    cmd = split_command(cmd)
    assert verify_sum_transaction(cmd) == "in"

    cmd1 = "sum 141"
    cmd1 = split_command(cmd1)
    try:
        x = verify_sum_transaction(cmd1)
    except ValueError:
        return None


def test_verify_replace_transaction():
    cmd = "replace 12 in life with 1200"
    cmd = split_command(cmd)
    assert verify_replace_transaction(cmd) == {'day': 12, 'value': 1200, 'type': "in", 'description': "life"}

    cmd1 = "replace 12 in man with what"
    cmd1 = split_command(cmd1)
    try:
        x = verify_replace_transaction(cmd1)
    except ValueError:
        return None


def test_verify_remove_transaction():
    cmd = "remove in"
    cmd = split_command(cmd)
    assert verify_remove_transaction(cmd) == "in"

    cmd1 = "remove 24 to 28"
    cmd1 = split_command(cmd1)
    assert verify_remove_transaction(cmd1)[0] == 24
    assert verify_remove_transaction(cmd1)[1] == 28

    cmd2 = "remove 12"
    cmd2 = split_command(cmd2)
    assert verify_remove_transaction(cmd2) == 12

    cmd3 = "remove wtf"
    cmd3 = split_command(cmd3)
    try:
        x = verify_remove_transaction(cmd3)
    except ValueError:
        return None


def test_verify_list_transaction():
    cmd = "list in"
    cmd = split_command(cmd)
    assert verify_list_transactions(cmd) == "in"

    cmd1 = "list balance 10"
    cmd1 = split_command(cmd1)
    assert verify_list_transactions(cmd1)[0] == "balance"
    assert verify_list_transactions(cmd1)[1] == 10

    cmd2 = "list > 141"
    cmd2 = split_command(cmd2)
    assert verify_list_transactions(cmd2)[0] == ">"
    assert verify_list_transactions(cmd2)[1] == 141

    cmd3 = "list something dude like 142"
    cmd3 = split_command(cmd3)
    try:
        x = verify_list_transactions(cmd3)
    except ValueError:
        return None


def test_add_insert():
    cmd = "insert 15 12 in air"
    cmd = split_command(cmd)
    l = []
    u = []
    add_insert(cmd, l, u)
    assert l[0] == {'day': 15, 'value': 12, 'type': "in", 'description': "air"}
    assert u[0][0] == "insert"
    assert u[0][1] == {'day': 15, 'value': 12, 'type': "in", 'description': "air"}

    bad_cmd = "insert 40 1200 out life"
    bad_cmd = split_command(bad_cmd)
    l_bad = []
    u_bad = []
    try:
        add_insert(bad_cmd, l_bad, u_bad)
    except ValueError:
        return None


def test_verify_add_insert():
    cmd = "insert 15 12 in air"
    cmd = split_command(cmd)
    transaction = verify_add_insert(cmd)
    assert transaction == {'day': 15, 'value': 12, 'type': "in", 'description': "air"}

    bad_cmd = "add 1200 fine fun"
    bad_cmd = split_command(bad_cmd)
    try:
        transaction = verify_add_insert(bad_cmd)
        assert transaction == None
    except ValueError:
        return None


def test_split_command():
    cmd = "add 12 in air"
    cmd1 = "list balance       =       10"
    cmd2 = "list"

    assert split_command(cmd) == ["add", "12", "in", "air"]
    assert split_command(cmd1) == ["list", "balance", "=", "10"]
    assert split_command(cmd2) == ["list"]


def test_create_transaction():
    day = 14
    value = 1200
    type = "in"
    description = "crimes"
    transaction = create_transaction(day, value, type, description)

    assert transaction["day"] == 14
    assert transaction["value"] == 1200
    assert transaction["type"] == "in"
    assert transaction["description"] == "crimes"


def test_validate_transaction():
    day = 14
    value = 1200
    type = "in"
    description = "crimes"
    transaction = create_transaction(day, value, type, description)

    assert transaction == validate_transaction(transaction)

    bad_day = 40
    bad_value = 1200
    bad_type = "in"
    bad_description = "891"
    bad_transaction = create_transaction(bad_day, bad_value, bad_type, bad_description)

    try:
        assert bad_transaction == validate_transaction(bad_transaction)
    except ValueError:
        return None


def test_gets():
    day = 14
    value = 1200
    type = "in"
    description = "crimes"
    transaction = create_transaction(day, value, type, description)
    cmd = "insert 12 190 in kids"
    cmd = split_command(cmd)

    assert get_day(transaction) == 14
    assert get_value(transaction) == 1200
    assert get_type(transaction) == "in"
    assert get_desc(transaction) == "crimes"
    assert get_action(cmd) == "insert"


def run_tests():
    test_create_transaction()
    test_validate_transaction()
    test_gets()
    test_split_command()
    test_add_insert()
    test_verify_add_insert()
    test_verify_list_transaction()
    test_verify_remove_transaction()
    test_verify_replace_transaction()
    test_verify_sum_transaction()
    test_verify_max_transaction()
    test_verify_filter_transaction()
    test_verify_undo_transaction()

run_ui()
run_tests()
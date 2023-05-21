"""
Created by @AlenMichael
November 2021
"""
import random


def verify_number(x):
    """
    :param x: Number to be verified
    :return: True if the number is valid, false if contrary
    """
    if x not in range(1000, 9999):
        return False
    l = x % 10
    x = x//10
    t = x % 10
    x = x//10
    s = x % 10
    x = x // 10
    f = x % 10
    if f == s or f == t or f == l:
        return False
    if s == t or s == l:
        return False
    if t == l:
        return False
    return True


def generate_random():
    """
    :return: True if the number generated is valid, false if contrary
    """
    while True:
        x = random.randint(1000, 9999)
        if verify_number(x):
            return x


def verify_runners_codes(x, y):
    """
    :param x: Computer's number
    :param y: User's number
    :return: Number of codes, Number of runners
    """
    runners = 0
    codes = 0
    l = x % 10
    x = x // 10
    t = x % 10
    x = x // 10
    s = x % 10
    x = x // 10
    f = x % 10
    x = [f, s, t, l]
    l = y % 10
    if l == x[3]:
        codes = codes + 1
    elif l in x:
        runners = runners + 1
    y = y // 10
    t = y % 10
    if t == x[2]:
        codes = codes + 1
    elif t in x:
        runners = runners + 1
    y = y // 10
    s = y % 10
    if s == x[1]:
        codes = codes + 1
    elif s in x:
        runners = runners + 1
    y = y // 10
    f = y % 10
    if f == x[0]:
        codes = codes + 1
    elif f in x:
        runners = runners + 1
    return codes, runners

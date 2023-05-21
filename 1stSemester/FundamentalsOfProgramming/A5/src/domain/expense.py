class Expense:

    def __init__(self, day, amount, typ):
        self.__day = day
        self.__amount = amount
        self.__typ = typ

    def get_day(self):
        return self.__day

    def get_amount(self):
        return self.__amount

    def get_typ(self):
        return self.__typ

    def set_amount(self, new_amount):
        self.__amount = new_amount

    def __eq__(self, other):
        return self.__day == other.__day and self.__typ == other.__typ

    def __str__(self):
        return "On day " + str(self.__day) + " you spent " + str(self.__amount) + " on " + str(self.__typ)


class IterableStructure:

    def __init__(self):
        self.__index = 0
        self.__list = []

    def __iter__(self):
        return iter(self.__list)

    def __delitem__(self, index):
        del self.__list[index]

    def __setitem__(self, index, expense):
        self.__list[index] = expense

    def __len__(self):
        return len(self.__list)

    def __getitem__(self, index):
        return self.__list[index]

    def append(self, expense):
        self.__list.append(expense)

    def get_all(self):
        return self.__list[:]


def gnome_sort(the_list, criteria):
    index = 0
    if not the_list:
        return
    length = len(the_list)
    while index < length:
        if not index:
            index = index + 1
        else:
            if not criteria(the_list[index], the_list[index + 1]):
                the_list[index], the_list[index + 1] = the_list[index + 1], the_list[index]
                index = index - 1
            else:
                index = index + 1
    return the_list

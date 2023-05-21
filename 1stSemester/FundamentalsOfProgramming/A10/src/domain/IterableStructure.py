class IterableStructure:

    def __init__(self):
        self.__index = 0
        self.__list = []

    def __iter__(self):
        return iter(self.__list)

    def __next__(self):
        if self.__index > len(self.__list) - 1:
            raise StopIteration
        else:
            self.__index = self.__index + 1
        return self.__list[self.__index]

    def __len__(self):
        return len(self.__list)

    def __getitem__(self, index):
        return self.__list[index]

    def __setitem__(self, index, value):
        self.__list[index] = value

    def __delitem__(self, index):
        del self.__list[index]

    def append(self, element):
        self.__list.append(element)

    def get_list(self):
        return self.__list[:]


def gnome_sort(the_list, function):
    index = 0
    length = len(the_list)
    if length == 1:
        return None
    elif length > 1:
        while index < length:
            if index == 0:
                index = index + 1
            if function(the_list[index], the_list[index-1]) is True:
                index = index + 1
            else:
                the_list[index], the_list[index-1] = the_list[index-1], the_list[index]
                index = index - 1
    else:
        raise IndexError("Can not sort null list")


def filtering(the_list, criteria):
    new_list = []
    for index in range(len(the_list)):
        if criteria(the_list[index]):
            new_list.append(the_list[index])
    return new_list[:]

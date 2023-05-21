class Student:

    def __init__(self, student_id, name, group):
        self.__student_id = student_id
        self.__name = name
        self.__group = group

    def get_student_id(self):
        return self.__student_id

    def get_name(self):
        return self.__name

    def get_group(self):
        return self.__group

    def set_name(self, new_name):
        self.__name = new_name

    def set_group(self, new_group):
        self.__group = new_group

    def __str__(self):
        return "Student ID:" + str(self.__student_id) + " Name:" + self.__name + " Group:" + str(self.__group)

    def __eq__(self, other):
        return self.__student_id == other.__student_id

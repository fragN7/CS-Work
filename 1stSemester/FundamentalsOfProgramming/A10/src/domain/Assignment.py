class Assignment:

    def __init__(self, assignment_id, description, deadline):
        self.__assignment_id = assignment_id
        self.__description = description
        self.__deadline = deadline

    def get_assignment_id(self):
        return self.__assignment_id

    def get_description(self):
        return self.__description

    def get_deadline(self):
        return self.__deadline

    def set_description(self, new_description):
        self.__description = new_description

    def set_deadline(self, new_deadline):
        self.__deadline = new_deadline

    def __str__(self):
        return "Assignment ID:" + str(self.__assignment_id) \
               + " Description:" + self.__description + " Deadline:" + self.__deadline

    def __eq__(self, other):
        return self.__assignment_id == other.__assignment_id

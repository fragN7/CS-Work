class Settings(object):

    def __init__(self, file_name):
        self.__fileName = file_name

    def __read_file(self):
        file_input = []
        try:
            file = open(self.__fileName)
            line = file.readline()
            while len(line) > 0:
                line = line.replace('\n', '')
                line = line.split("=")
                file_input.append(line)
                line = file.readline()
            file.close()
        except None as io:
            print(str(io))
        return file_input[:]

    def config_settings(self):
        file_input = self.__read_file()
        if not file_input:
            return None
        try:
            return file_input[0][1], file_input[1][1], file_input[2][1], file_input[3][1]
        except IndexError:
            print("Settings file error")

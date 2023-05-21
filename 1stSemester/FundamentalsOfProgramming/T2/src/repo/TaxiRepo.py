from src.errors.exceptions import RepoError


class RepoTaxi:

    def __init__(self):
        self.__repo_taxi = []

    def __len__(self):
        return len(self.__repo_taxi)

    def add(self, taxi):
        if taxi in self.__repo_taxi:
            raise RepoError("Taxi already exists")
        self.__repo_taxi.append(taxi)

    def remove(self, taxi):
        if taxi not in self.__repo_taxi:
            raise RepoError("Taxi doesn't exist")
        for i in range(len(self.__repo_taxi)):
            if self.__repo_taxi[i] == taxi:
                del self.__repo_taxi[i]
                return

    def find_id(self, taxi_id):
        for i in self.__repo_taxi:
            if i.get_taxi_id() == taxi_id:
                return i
        raise RepoError("Taxi doesn't exist")

    def get_all_taxis(self):
        return self.__repo_taxi[:]

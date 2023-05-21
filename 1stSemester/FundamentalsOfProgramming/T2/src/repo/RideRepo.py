from src.errors.exceptions import RepoError


class RepoRide:

    def __init__(self):
        self.__repo_ride = []

    def __len__(self):
        return len(self.__repo_ride)

    def add(self, ride):
        if ride in self.__repo_ride:
            raise RepoError("Ride already exists")
        self.__repo_ride.append(ride)

    def remove(self, ride):
        if ride not in self.__repo_ride:
            raise RepoError("Ride doesn't exist")
        for i in range(len(self.__repo_ride)):
            if self.__repo_ride[i] == ride:
                del self.__repo_ride[i]
                return

    def get_all_rides(self):
        return self.__repo_ride[:]

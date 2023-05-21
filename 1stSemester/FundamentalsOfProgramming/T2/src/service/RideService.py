from src.domain.ride import Ride


class ServiceRide:

    def __init__(self, repo_ride):
        self.repo_ride = repo_ride

    def add_ride(self, x, y):
        ride = Ride(x, y)
        self.repo_ride.add(ride)

    def remove_ride(self, x, y):
        ride = Ride(x, y)
        self.repo_ride.remove(ride)

    def get_rides(self):
        return self.repo_ride.get_all_rides()

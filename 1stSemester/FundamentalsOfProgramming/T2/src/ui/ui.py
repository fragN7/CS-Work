from src.domain.ride import Ride


class UserInterface:

    def __init__(self, service_taxi, service_ride, service_population):
        self.service_taxi = service_taxi
        self.service_ride = service_ride
        self.service_population = service_population

    def __print_taxi(self):
        taxis = self.service_taxi.get_taxis()
        if not taxis:
            print("No taxis")
            return
        for i in taxis:
            print(i)

    def __add_ride(self):
        x = int(input("Enter starting location"))
        y = int(input("Enter ending location"))
        self.service_ride.add_ride(x, y)

    def __calculate_closest(self):
        rides = self.service_ride.get_rides()
        location_ride = rides[0]
        maxim = 10000
        taxis = self.service_taxi.get_taxis()
        for i in taxis:
            location = i.get_location()
            x = location[0]
            y = location[1]
            taxi_ride = Ride(x, y)
            if location_ride.get_distance(taxi_ride) < maxim:
                maxim = location_ride.get_distance(taxi_ride)
                best_taxi = i
        if maxim != 10000:
            best_taxi.set_total_fares(maxim)
            best_taxi.set_location(location_ride)
            print("Best Taxi is: \n", best_taxi)

    def run(self):
        print("Welcome to TaxiLand")
        n = int(input("Please enter a number 1-10\n"))
        self.service_population.populate_list(n)
        self.__print_taxi()
        self.__add_ride()
        self.__calculate_closest()
        self.__print_taxi()

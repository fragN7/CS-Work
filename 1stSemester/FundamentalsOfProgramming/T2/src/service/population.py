import random


class Population:

    def __init__(self, service_taxi):
        self.service_taxi = service_taxi

    def add_taxis(self, n):
        for i in range(n):
            number = random.randint(0, 100)
            other_number = random.randint(0, 100)
            location = [number, other_number]
            self.service_taxi.add_taxi(i, location, 0)

    def populate_list(self, n):
        self.add_taxis(n)

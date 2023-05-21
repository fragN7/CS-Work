class Taxi:

    def __init__(self, taxi_id, location, total_fares=0):
        self.taxi_id = taxi_id
        self.location = location
        self.total_fares = total_fares

    def get_taxi_id(self):
        return self.taxi_id

    def get_location(self):
        return self.location

    def set_location(self, new_location):
        self.location = new_location

    def get_total_fares(self):
        return self.total_fares

    def set_total_fares(self, new_fare):
        self.total_fares = new_fare

    def __eq__(self, other):
        return self.taxi_id == other.taxi_id

    def __str__(self):
        return "Taxi ID:" + str(self.taxi_id) + " Total fares:" + str(self.total_fares)

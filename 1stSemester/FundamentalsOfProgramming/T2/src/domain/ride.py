class Ride:

    def __init__(self, start_location, end_location):
        self.start_location = start_location
        self.end_location = end_location

    def get_start_location(self):
        return self.start_location

    def get_end_location(self):
        return self.end_location

    def get_distance(self, other):
        return abs(self.start_location - other.start_location) + abs(self.end_location - other.end_location)

    def __eq__(self, other):
        return self.start_location == other.start_location and self.end_location == other.start_location
from src.domain.taxi import Taxi


class ServiceTaxi:

    def __init__(self, repo_taxi):
        self.repo_taxi = repo_taxi

    def add_taxi(self, id_taxi, location, total_fares):
        taxi = Taxi(id_taxi, location, total_fares)
        self.repo_taxi.add(taxi)

    def remove_taxi(self, id_taxi):
        taxi = self.repo_taxi.find_id(id_taxi)
        self.repo_taxi.remove(taxi)

    def get_taxis(self):
        return self.repo_taxi.get_all_taxis()

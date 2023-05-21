from src.service.TaxiService import ServiceTaxi
from src.service.RideService import ServiceRide
from src.service.population import Population

from src.repo.TaxiRepo import RepoTaxi
from src.repo.RideRepo import RepoRide

from src.ui.ui import UserInterface


if __name__ == '__main__':

    repo_taxi = RepoTaxi()
    service_taxi = ServiceTaxi(repo_taxi)

    repo_ride = RepoRide()
    service_ride = ServiceRide(repo_ride)

    service_population = Population(service_taxi)
    us = UserInterface(service_taxi, service_ride, service_population)
    us.run()

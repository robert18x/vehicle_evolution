/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#pragma once
#include "car.h"
#include <utility>

class EvolutionAlgorithm {
  public:
    struct Parameters {
        double crossoverProbability;
        double mutationProbability;
        double mutationRate;
    };

    EvolutionAlgorithm(Parameters parameters);

    ~EvolutionAlgorithm() = default;
    EvolutionAlgorithm(const EvolutionAlgorithm&) = delete;
    EvolutionAlgorithm(EvolutionAlgorithm&&) = delete;
    std::vector<Car::Configuration> evolve(std::vector<std::pair<Car::Distance, Car::Configuration>>& configuration);
  private:
    std::vector<Car::Configuration> select(std::vector<std::pair<Car::Distance, Car::Configuration>>& previousConfigurations);
    Car::Configuration tournamentSelection(const std::vector<std::pair<Car::Distance, Car::Configuration>>& previousConfigurations);
    void crossover(std::vector<Car::Configuration>& configurations);
    Car::Configuration crossoverIndividuals(const Car::Configuration& first, const Car::Configuration& second);
    void mutate(std::vector<Car::Configuration>& configurations);
    void mutateIndividual(Car::Configuration& individual);

    template <typename T>
    static T mutation(double mutationRate, double a = 0.0, double b = 1.0);

    Parameters parameters;
};

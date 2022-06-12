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
    EvolutionAlgorithm();

    ~EvolutionAlgorithm() = default;
    EvolutionAlgorithm(const EvolutionAlgorithm&) = delete;
    EvolutionAlgorithm(EvolutionAlgorithm&&) = delete;
    typedef float Distance; // temporary
    std::vector<Car::Configuration> evolve(std::vector<std::pair<Distance, Car::Configuration>>& configuration);
  private:
    std::vector<Car::Configuration> select(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations);
    Car::Configuration tournamentSelection(const std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations);
    void crossover(std::vector<Car::Configuration>& newConfigurations);
    void mutate(std::vector<Car::Configuration>& newConfigurations);


};

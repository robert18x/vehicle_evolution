/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#include "evolution_algorithm.h"

#include <algorithm>
#include <execution>

std::vector<Car::Configuration> EvolutionAlgorithm::evolve(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    std::sort(std::execution::par_unseq, previousConfigurations.begin(), previousConfigurations.end(),
              [](auto& elem1, auto& elem2) { return elem1.first >= elem2.first; });
    std::vector<Car::Configuration> newConfigurations = select(previousConfigurations);
    crossover(newConfigurations);
    mutate(newConfigurations);
    return newConfigurations;
}

std::vector<Car::Configuration> EvolutionAlgorithm::select(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    return {}; // TODO
}


void EvolutionAlgorithm::crossover(std::vector<Car::Configuration>& newConfigurations) {

}

void EvolutionAlgorithm::mutate(std::vector<Car::Configuration>& newConfigurations) {

}


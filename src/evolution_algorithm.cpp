/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#include "evolution_algorithm.h"

#include <algorithm>
#include <execution>
#include "utils.h"

std::vector<Car::Configuration> EvolutionAlgorithm::evolve(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    std::sort(std::execution::par_unseq, previousConfigurations.begin(), previousConfigurations.end(),
              [](auto& elem1, auto& elem2) { return elem1.first >= elem2.first; });
    std::vector<Car::Configuration> newConfigurations = select(previousConfigurations);
    crossover(newConfigurations);
    mutate(newConfigurations);
    return newConfigurations;
}

std::vector<Car::Configuration> EvolutionAlgorithm::select(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    std::vector<Car::Configuration> newConfigurations;
    newConfigurations.resize(previousConfigurations.size());
    std::for_each(std::execution::par_unseq, newConfigurations.begin(), newConfigurations.end(), [this, &previousConfigurations] (auto& elem) {
        elem = tournamentSelection(previousConfigurations);
    });
    return newConfigurations;
}

Car::Configuration EvolutionAlgorithm::tournamentSelection(const std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    auto i = utils::random<std::size_t>(0, previousConfigurations.size());
    auto j = utils::random<std::size_t>(0, previousConfigurations.size());
    auto& individual1 = previousConfigurations[i];
    auto& individual2 = previousConfigurations[j];
    auto distance = [](const std::pair<Distance, Car::Configuration>& individual) -> Distance { return individual.first; };
    if (distance(individual1) > distance(individual2)) {
        return individual1.second;
    } else {
        return individual2.second;
    }
}

void EvolutionAlgorithm::crossover(std::vector<Car::Configuration>& newConfigurations) {

}

void EvolutionAlgorithm::mutate(std::vector<Car::Configuration>& newConfigurations) {

}


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
#include "config.h"

std::vector<Car::Configuration> EvolutionAlgorithm::evolve(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    std::sort(std::execution::par_unseq, previousConfigurations.begin(), previousConfigurations.end(),
              [](auto& elem1, auto& elem2) { return elem1.first >= elem2.first; });
    std::vector<Car::Configuration> newConfigurations = select(previousConfigurations);
    crossover(newConfigurations);
    mutate(newConfigurations);
    return newConfigurations;
}

std::vector<Car::Configuration> EvolutionAlgorithm::select(std::vector<std::pair<Distance, Car::Configuration>>& previousConfigurations) {
    std::vector<Car::Configuration> newConfigurations(previousConfigurations.size());
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

void EvolutionAlgorithm::crossover(std::vector<Car::Configuration>& configurations) {
    std::vector<Car::Configuration> originalConfigurations = configurations;
    std::for_each(std::execution::par_unseq, configurations.begin(), configurations.end(), [this, &originalConfigurations] (auto& elem) {
        if (utils::random(0.0, 1.0) <= crossoverProbability) {
            auto otherElemIndex = utils::random<std::size_t>(0, originalConfigurations.size() - 1);
            auto& otherElem = originalConfigurations[otherElemIndex];
            elem = crossoverIndividuals(elem, otherElem);
        }
    });
}

Car::Configuration EvolutionAlgorithm::crossoverIndividuals(const Car::Configuration& first, const Car::Configuration& second) {
    Car::Configuration crossoveredConfiguration;
    crossoveredConfiguration.wheel1Vertex = (first.wheel1Vertex + second.wheel1Vertex) / 2;
    crossoveredConfiguration.wheel2Vertex = (first.wheel2Vertex + second.wheel2Vertex) / 2;
    return crossoveredConfiguration;
}

void EvolutionAlgorithm::mutate(std::vector<Car::Configuration>& configurations) {
    std::for_each(std::execution::par_unseq, configurations.begin(), configurations.end(), [this] (auto& elem) {
        if (utils::random(0.0, 1.0) <= mutationProbability) {
            mutateIndividual(elem);
        }
    });
}

void EvolutionAlgorithm::mutateIndividual(Car::Configuration& individual) {

    individual.wheel1Vertex += mutation<int>() % Car::maxVertices;
    individual.wheel2Vertex += mutation<int>() % Car::maxVertices;
    individual.wheel1Radius += mutation<double>();
    individual.wheel2Radius += mutation<double>();

    auto random = utils::random(0.0, 1.0);
    if (random < 0.33 and individual.vertices.size() > 3) {
        individual.vertices.pop_back();
    } else if (random < 0.66 and individual.vertices.size() < Car::maxVertices) {
        auto x = utils::random(0.f, 8.f);
        auto y = utils::random(0.f, 8.f);
        individual.vertices.emplace_back(x, y);
    }

    for (auto& vertices : individual.vertices) {
        float x = vertices.x + mutation<float>();
        float y = vertices.y + mutation<float>();
        vertices.Set(x, y);
    }
}

template <typename T>
T EvolutionAlgorithm::mutation(double a, double b) {
    return static_cast<T>(utils::normal_distribution(a, b) * mutationRate);
}

/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#include "evolution_algorithm.h"

#include <algorithm>
#include <execution>
#include <utility>
#include <box2d/box2d.h>
#include "utils.h"

/**
 * @brief Construct a new Evolution Algorithm:: Evolution Algorithm object
 *
 * @param parameters - parameters of evolution algorithm.
 */
EvolutionAlgorithm::EvolutionAlgorithm(Parameters parameters) : parameters(parameters) {}


/**
 * @brief take one step of evolution algorithm.
 *
 * @param previousConfigurations - configurations on which evolution will be done.
 * @return std::vector<Car::Configuration>
 */
std::vector<Car::Configuration> EvolutionAlgorithm::evolve(std::vector<std::pair<Car::Distance, Car::Configuration>>& previousConfigurations) {
    std::sort(std::execution::par_unseq, previousConfigurations.begin(), previousConfigurations.end(),
              [](auto& elem1, auto& elem2) { return elem1.first >= elem2.first; });
    std::vector<Car::Configuration> newConfigurations = select(previousConfigurations);
    crossover(newConfigurations);
    mutate(newConfigurations);
    return newConfigurations;
}

std::vector<Car::Configuration> EvolutionAlgorithm::select(std::vector<std::pair<Car::Distance, Car::Configuration>>& previousConfigurations) {
    std::vector<Car::Configuration> newConfigurations(previousConfigurations.size());
    std::for_each(std::execution::par_unseq, newConfigurations.begin(), newConfigurations.end(), [this, &previousConfigurations] (auto& elem) {
        elem = tournamentSelection(previousConfigurations);
    });
    return newConfigurations;
}

Car::Configuration EvolutionAlgorithm::tournamentSelection(const std::vector<std::pair<Car::Distance, Car::Configuration>>& previousConfigurations) {
    auto i = utils::random<std::size_t>(0, previousConfigurations.size() - 1);
    auto j = utils::random<std::size_t>(0, previousConfigurations.size() - 1);
    auto& individual1 = previousConfigurations[i];
    auto& individual2 = previousConfigurations[j];
    auto distance = [](const std::pair<Car::Distance, Car::Configuration>& individual) { return individual.first; };
    if (distance(individual1) > distance(individual2)) {
        return individual1.second;
    } else {
        return individual2.second;
    }
}

void EvolutionAlgorithm::crossover(std::vector<Car::Configuration>& configurations) {
    std::vector<Car::Configuration> originalConfigurations = configurations;
    std::for_each(configurations.begin(), configurations.end(), [this, &originalConfigurations] (auto& elem) {
        if (utils::random(0.0, 1.0) <= parameters.crossoverProbability) {
            auto otherElemIndex = utils::random<std::size_t>(0, originalConfigurations.size() - 1);
            auto& otherElem = originalConfigurations[otherElemIndex];
            elem = crossoverIndividuals(elem, otherElem);
        }
    });
}

Car::Configuration EvolutionAlgorithm::crossoverIndividuals(const Car::Configuration& first, const Car::Configuration& second) {
    std::vector<b2Vec2> newVertices;
    newVertices.reserve(first.vertices.size());
    for (std::size_t i = 0; i < first.vertices.size(); ++i) {
        auto& firstVertex = first.vertices[i];
        if (i < second.vertices.size()) {
            auto& secondVertex = second.vertices[i];
            auto point = utils::random(0.0f, 1.0f);
            float x = firstVertex.x * point + secondVertex.x * (1.0f - point);
            float y = firstVertex.y * point + secondVertex.y * (1.0f - point);
            newVertices.emplace_back(x, y);
        } else {
            newVertices.emplace_back(firstVertex.x, firstVertex.y);
        }
    }

    double wheel1Point = utils::random(0.0, 1.0);
    double newWheel1Radius = first.wheel1Radius * wheel1Point + second.wheel1Radius * (1.0 - wheel1Point);

    double wheel2Point = utils::random(0.0, 1.0);
    double newWheel2Radius = first.wheel2Radius * wheel2Point + second.wheel2Radius * (1.0 - wheel2Point);


    return {std::move(newVertices), first.wheel1Vertex, first.wheel2Vertex, newWheel1Radius, newWheel2Radius};
}

void EvolutionAlgorithm::mutate(std::vector<Car::Configuration>& configurations) {
    std::for_each(configurations.begin(), configurations.end(), [this] (auto& elem) {
        if (utils::random(0.0, 1.0) <= parameters.mutationProbability) {
            mutateIndividual(elem);
        }
    });
}

void EvolutionAlgorithm::mutateIndividual(Car::Configuration& individual) {
    auto random = utils::random(0.0, 1.0);
    if (random < 0.33 and individual.vertices.size() > 3) {
        individual.vertices.pop_back();
    } else if (random < 0.66 and individual.vertices.size() < Car::maxVertices) {
        float x = utils::random(Car::minCarX, Car::maxCarX);
        float y = utils::random(Car::minCarY, Car::maxCarY);
        individual.vertices.emplace_back(x, y);
    }

    auto& mr = parameters.mutationRate;
    for (auto& vertices : individual.vertices) {
        float x = vertices.x + mutation<float>(mr);
        float y = vertices.y + mutation<float>(mr);
        vertices.Set(x, y);
    }

    individual.wheel1Vertex = (individual.wheel1Vertex + mutation<int>(mr)) % individual.vertices.size();
    individual.wheel2Vertex = (individual.wheel2Vertex + mutation<int>(mr)) % individual.vertices.size();
    individual.wheel1Radius = std::min(individual.wheel1Radius + mutation<double>(mr), Car::maxWheelRadius);
    individual.wheel2Radius = std::max(individual.wheel2Radius + mutation<double>(mr), Car::minWheelRadius);
}

template <typename T>
T EvolutionAlgorithm::mutation(double mutationRate, double a, double b) {
    return static_cast<T>(utils::normal_distribution(a, b) * mutationRate);
}

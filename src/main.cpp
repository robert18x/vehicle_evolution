/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#include <box2d/box2d.h>

#include <iostream>
#include "draw.h"
#include "window.h"
#include "evolution_algorithm.h"
#include "world.h"
#include <chrono>


void runProgram() {
    Window window("Vehicle evolution", {400, 400});
    int nCars = 100;
    World world(nCars);

    int epochTimeInSeconds = 15;
    EvolutionAlgorithm::Parameters evolutionParams = { 0.3, 0.7, 0.1 };

    std::chrono::steady_clock::time_point epochStart = std::chrono::steady_clock::now();
    while (not window.shouldClose()) {
        window.newFrame();

        world.step();

        window.renderFrame();

        if (std::chrono::steady_clock::now() > epochStart + std::chrono::seconds(epochTimeInSeconds)) {
            EvolutionAlgorithm evolutionAlgorithm(evolutionParams);
            auto carData = world.getCarData();
            auto newCarConfigurations = evolutionAlgorithm.evolve(carData);
            world.createNewCars(newCarConfigurations);
            epochStart = std::chrono::steady_clock::now();
        }
    }
}

int main(int, char**) {
    try {
        runProgram();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#pragma once
#include "car.h"

class EvolutionAlgorithm {
  public:
    EvolutionAlgorithm();

    ~EvolutionAlgorithm() = default;
    EvolutionAlgorithm(const EvolutionAlgorithm&) = delete;
    EvolutionAlgorithm(EvolutionAlgorithm&&) = delete;

    void evolve();
  private:

};

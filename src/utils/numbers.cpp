#include "game/utils/numbers.h"

#include <random>

inline std::mt19937 rng{ std::random_device{}() };

bool randomChance(float probability)
{
    std::bernoulli_distribution dist(probability);
    return dist(rng);
}

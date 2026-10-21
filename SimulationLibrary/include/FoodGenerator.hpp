#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP

#pragma once

#include "Food.hpp"
#include "MapBounds.hpp"

#include <random>

namespace Simulation
{

class FoodGenerator
{
public:
    explicit FoodGenerator(unsigned int seed)
        : mRandomEngine { seed }
    {
    }

    Food generate(const MapBounds& bounds)
    {
        std::uniform_real_distribution<double> xDistribution {
            bounds.minimumX(),
            bounds.maximumX()
        };

        std::uniform_real_distribution<double> yDistribution {
            bounds.minimumY(),
            bounds.maximumY()
        };

        const Position position {
            xDistribution(mRandomEngine),
            yDistribution(mRandomEngine)
        };

        return Food { position };
    }

private:
    std::mt19937 mRandomEngine;
};

}

#endif

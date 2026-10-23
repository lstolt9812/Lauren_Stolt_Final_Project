#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP

#pragma once

#include "Food.hpp"
#include "MapBounds.hpp"

#include <random>
#include <vector>

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
    std::vector<Food> generateMultiple(
        const MapBounds& bounds,
        std::size_t count)
    {
        std::vector<Food> foods;

        for (std::size_t index = 0; index < count; ++index)
        {
            foods.push_back(generate(bounds));
        }

        return foods;
    }

private:
    std::mt19937 mRandomEngine;
};

}

#endif

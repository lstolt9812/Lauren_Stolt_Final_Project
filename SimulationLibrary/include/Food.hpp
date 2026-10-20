#ifndef FOOD_HPP
#define FOOD_HPP

#pragma once

#include "Position.hpp"

namespace Simulation
{

class Food
{
public:
    explicit Food(Position position)
        : mPosition { position }
    {
    }

    Position position() const
    {
        return mPosition;
    }

private:
    Position mPosition;
};

}

#endif

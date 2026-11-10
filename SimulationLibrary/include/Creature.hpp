#ifndef CREATURE_H
#define CREATURE_H

#include "MapBounds.hpp"
#include "Position.hpp"

namespace Simulation
{

class Creature
{
public:
    Creature(const Position& position):
        mPosition
    {
        position
    }
    {
    }

    Position position() const
    {
        return mPosition;
    }

    void moveBy(double changeInX, double changeInY)
    {
        mPosition.x += changeInX;
        mPosition.y += changeInY;
    }

    void moveBy(
        double changeInX,
        double changeInY,
        const MapBounds& bounds)
    {
        const Position proposedPosition
        {
            mPosition.x + changeInX,
            mPosition.y + changeInY
        };

        if (bounds.contains(proposedPosition))
        {
            mPosition = proposedPosition;
        }
    }

private:
    Position mPosition;
};
};

#endif

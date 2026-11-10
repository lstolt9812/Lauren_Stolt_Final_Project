#ifndef CREATURE_H
#define CREATURE_H

#include "Food.hpp"
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

    double radius() const
    {
        return mRadius;
    }

    void growBy(double amount)
    {
        mRadius += amount;
    }

    bool overlaps(const Food& food) const
    {
        const Position foodPosition = food.position();

        const double changeInX =
            foodPosition.x - mPosition.x;

        const double changeInY =
            foodPosition.y - mPosition.y;

        const double squaredDistance =
            changeInX * changeInX
            + changeInY * changeInY;

        const double squaredRadius =
            mRadius * mRadius;

        return squaredDistance <= squaredRadius;
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
    double mRadius {2.0};
};
};

#endif

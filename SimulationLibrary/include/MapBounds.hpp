#ifndef MAPBOUNDS_H
#define MAPBOUNDS_H

#pragma once

#include "Position.hpp"

namespace Simulation
{

class MapBounds
{
public:
    MapBounds(
        double minimumX,
        double maximumX,
        double minimumY,
        double maximumY)
        : mMinimumX { minimumX }
        , mMaximumX { maximumX }
        , mMinimumY { minimumY }
        , mMaximumY { maximumY }
    {
    }

    bool contains(Position position) const
    {
        return position.x >= mMinimumX
               && position.x <= mMaximumX
               && position.y >= mMinimumY
               && position.y <= mMaximumY;
    }

    double minimumX() const
    {
        return mMinimumX;
    }

    double maximumX() const
    {
        return mMaximumX;
    }

    double minimumY() const
    {
        return mMinimumY;
    }

    double maximumY() const
    {
        return mMaximumY;
    }

private:
    double mMinimumX;
    double mMaximumX;
    double mMinimumY;
    double mMaximumY;
};

}

#endif

#include "gtest/gtest.h"

#include "Position.hpp"

TEST(PositionTest, DefaultsToOrigin)
{
    const Simulation::Position position;

    EXPECT_DOUBLE_EQ(position.x, 0.0);
    EXPECT_DOUBLE_EQ(position.y, 0.0);
}

TEST(PositionTest, StoresGivenCoordinates)
{
    const Simulation::Position position { 15.0, -8.0 };

    EXPECT_DOUBLE_EQ(position.x, 15.0);
    EXPECT_DOUBLE_EQ(position.y, -8.0);
}

TEST(PositionTest, CoordinatesCanBeChanged)
{
    Simulation::Position position;

    position.x = 12.5;
    position.y = 7.25;

    EXPECT_DOUBLE_EQ(position.x, 12.5);
    EXPECT_DOUBLE_EQ(position.y, 7.25);
}
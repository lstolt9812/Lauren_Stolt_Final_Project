#include "gtest/gtest.h"

#include "Food.hpp"
#include "FoodGenerator.hpp"
#include "MapBounds.hpp"
#include "Position.hpp"
#include <vector>

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

TEST(FoodTest, StoresGivenPosition)
{
    const Simulation::Position position { 4.5, -2.0 };

    const Simulation::Food food { position };

    EXPECT_DOUBLE_EQ(food.position().x, 4.5);
    EXPECT_DOUBLE_EQ(food.position().y, -2.0);
}

TEST(MapBoundsTest, ContainsPositionInMiddle)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    const Simulation::Position position { 0.0, 0.0 };

    EXPECT_TRUE(bounds.contains(position));
}

TEST(MapBoundsTest, DoesNotContainPositionBeyondMaximumX)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    const Simulation::Position position { 11.0, 0.0 };

    EXPECT_FALSE(bounds.contains(position));
}

TEST(MapBoundsTest, DoesNotContainPositionBeyondMaximumY)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    const Simulation::Position position { -11.0, 0.0 };

    EXPECT_FALSE(bounds.contains(position));
}

TEST(MapBoundsTest, DoesNotContainPositionBeyondMinimumY)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    const Simulation::Position position { 0.0, -11.0 };

    EXPECT_FALSE(bounds.contains(position));
}

TEST(MapBoundsTest, ContainsPositionOnBoundary)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    const Simulation::Position position { 10.0, 0.0 };

    EXPECT_TRUE(bounds.contains(position));
}

TEST(FoodGenerationTest, FoodPositionIsInsideMapBounds)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    const Simulation::Position position { 5.0, 0 };
    const Simulation::Food food { position };

    EXPECT_TRUE(bounds.contains(food.position()));
}

TEST(MapBoundsTest, ReportsMinimumX)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    EXPECT_DOUBLE_EQ(bounds.minimumX(), -10.0);
}

TEST(MapBoundsTest, ReportsMaximumX)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    EXPECT_DOUBLE_EQ(bounds.maximumX(), 10.0);
}

TEST(MapBoundsTest, ReportsMinimumY)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    EXPECT_DOUBLE_EQ(bounds.minimumY(), -10.0);
}

TEST(MapBoundsTest, ReportsMaximumY)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    EXPECT_DOUBLE_EQ(bounds.maximumY(), 10.0);
}

TEST(FoodGeneratorTest, GeneratesFoodInsideMapBounds)
{
    const Simulation::MapBounds bounds
    {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    Simulation::FoodGenerator generator { 42 };

    const Simulation::Food food = generator.generate(bounds);

    EXPECT_TRUE(bounds.contains(food.position()));
}

TEST(FoodGeneratorTest, SameSeedGeneratesSameFirstPosition)
{
    const Simulation::MapBounds bounds {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    Simulation::FoodGenerator firstGenerator { 42 };
    Simulation::FoodGenerator secondGenerator { 42 };

    const Simulation::Food firstFood =
        firstGenerator.generate(bounds);

    const Simulation::Food secondFood =
        secondGenerator.generate(bounds);

    EXPECT_DOUBLE_EQ(
        firstFood.position().x,
        secondFood.position().x
        );

    EXPECT_DOUBLE_EQ(
        firstFood.position().y,
        secondFood.position().y
        );
}

TEST(FoodGeneratorTest, GeneratesRequestedNumberOfFoodObjects)
{
    const Simulation::MapBounds bounds{
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    Simulation::FoodGenerator generator{1234};

    const std::vector<Simulation::Food> foods =
        generator.generateMultiple(bounds, 5);

    EXPECT_EQ(foods.size(), 5);
}

TEST(FoodGeneratorTest, AllGeneratedFoodObjectsAreInsideMapBounds)
{
    const Simulation::MapBounds bounds {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    Simulation::FoodGenerator generator { 1234 };

    const std::vector<Simulation::Food> foods =
        generator.generateMultiple(bounds, 5);

    for (const Simulation::Food& food : foods)
    {
        EXPECT_TRUE(bounds.contains(food.position()));
    }
}

TEST(FoodGeneratorTest, RequestingZeroFoodObjectsReturnsEmptyCollection)
{
    const Simulation::MapBounds bounds {
        -10.0,
        10.0,
        -10.0,
        10.0
    };

    Simulation::FoodGenerator generator { 1234 };

    const std::vector<Simulation::Food> foods =
        generator.generateMultiple(bounds, 0);

    EXPECT_TRUE(foods.empty());
}
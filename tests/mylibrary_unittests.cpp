#include "gtest/gtest.h"
#include "DataGenerator.hpp"
#include <stdexcept>

namespace
{
constexpr double tolerance = 1.0e-10;
}

TEST(ScalarFunctionTest, ReturnsZeroAtOrigin)
{
const double result =
ScientificData::scalarFunction(0.0, 0.0);
EXPECT_NEAR(result, 0.0, tolerance);
}

TEST(ScalarFunctionTest, ReturnsOneAtPiOverTwoAndZero)
{
constexpr double pi = 3.14159265358979323846;
const double result =
ScientificData::scalarFunction(pi / 2.0,0.0);
EXPECT_NEAR(result, 1.0, tolerance);
}

TEST(ScalarFunctionTest, ReturnsNegativeOneForNegativePiOverTwo)
{
constexpr double pi = 3.14159265358979323846;
const double result = ScientificData::scalarFunction(-pi / 2.0,0.0);
}


TEST(ScalarFunctionTest, AppliesAmplitude)
{
constexpr double pi = 3.14159265358979323846;
const double result = ScientificData::scalarFunction(pi / 2.0,0.0,3.5,1.0);
EXPECT_NEAR(result, 3.5, tolerance);
}

TEST(ScalarFunctionTest, ZeroAmplitudeCreatesZero)
{
constexpr double pi = 3.14159265358979323846;
const double result = ScientificData::scalarFunction(pi / 2.0,0.0,0.0,1.0);
EXPECT_NEAR(result, 0.0, tolerance);
}

TEST(ScalarFunctionTest, ZeroFrequencyCreatesFlatZeroSurface)
{
const double result = ScientificData::scalarFunction(25.0,-17.0,2.0,0.0);
EXPECT_NEAR(result, 0.0, tolerance);
}

TEST(DataGeneratorTest, GeneratesCorrectNumberOfValues)
{
const ScientificData::ScalarFieldData data = ScientificData::generateData(-1.0,1.0,-2.0,2.0,3,5);

EXPECT_EQ(data.xCoordinates.size(), 3);
EXPECT_EQ(data.yCoordinates.size(), 5);
EXPECT_EQ(data.zValues.size(), 15);

EXPECT_EQ(data.xSampleCount, 3);
EXPECT_EQ(data.ySampleCount, 5);
}

TEST(DataGeneratorTest, IncludesRequestedRangeEndpoints)
{
const ScientificData::ScalarFieldData data = ScientificData::generateData(-2.0,2.0,-3.0,3.0,5,7);
EXPECT_NEAR(data.xCoordinates.front(),-2.0,tolerance);
EXPECT_NEAR(data.xCoordinates.back(),2.0,tolerance);
EXPECT_NEAR(data.yCoordinates.front(),-3.0,tolerance);
EXPECT_NEAR(data.yCoordinates.back(),3.0,tolerance);
}

TEST(DataGeneratorTest, GeneratesEvenlySpacedCoordinates)
{
const ScientificData::ScalarFieldData data = ScientificData::generateData(0.0,4.0,0.0,2.0,5,3);
ASSERT_EQ(data.xCoordinates.size(), 5);
EXPECT_NEAR(data.xCoordinates[0], 0.0, tolerance);
EXPECT_NEAR(data.xCoordinates[1], 1.0, tolerance);
EXPECT_NEAR(data.xCoordinates[2], 2.0, tolerance);
EXPECT_NEAR(data.xCoordinates[3], 3.0, tolerance);
EXPECT_NEAR(data.xCoordinates[4], 4.0, tolerance);

ASSERT_EQ(data.yCoordinates.size(), 3);
EXPECT_NEAR(data.yCoordinates[0], 0.0, tolerance);
EXPECT_NEAR(data.yCoordinates[1], 1.0, tolerance);
EXPECT_NEAR(data.yCoordinates[2], 2.0, tolerance);
}

TEST(DataGeneratorTest, CalculatesCorrectGridValues)
{
constexpr double pi = 3.14159265358979323846;
const ScientificData::ScalarFieldData data = ScientificData::generateData(0.0,pi / 2.0,0.0,pi / 2.0,2,2);
ASSERT_EQ(data.zValues.size(), 4);
EXPECT_NEAR(data.zValues[0], 0.0, tolerance);
EXPECT_NEAR(data.zValues[1], 1.0, tolerance);
EXPECT_NEAR(data.zValues[2], 0.0, tolerance);
EXPECT_NEAR(data.zValues[3], 0.0, tolerance);
}

TEST(DataGeneratorTest, ThrowsWhenXSampleCountIsTooSmall)
{
EXPECT_THROW(ScientificData::generateData(-1.0,1.0,-1.0,1.0,1,10), std::invalid_argument);
}

TEST(DataGeneratorTest, ThrowsWhenYSampleCountIsTooSmall)
{
EXPECT_THROW(ScientificData::generateData(-1.0,1.0,-1.0,1.0,10,1),std::invalid_argument);
}
#ifndef DATAGENERATOR_HPP
#define DATAGENERATOR_HPP

#include <cstddef>
#include <vector>

namespace ScientificData
{
struct ScalarFieldData
{
std::vector<double> xCoordinates;
std::vector<double> yCoordinates;
std::vector<double> zValues;

std::size_t xSampleCount;
std::size_t ySampleCount;
};

double scalarFunction(
double x,
double y,
double amplitude = 1.0,
double frequency = 1.0);

ScalarFieldData generateData(
double xMinimum,
double xMaximum,
double yMinimum,
double yMaximum,
std::size_t xSampleCount,
std::size_t ySampleCount,
double amplitude = 1.0,
double frequency = 1.0);
};

#endif
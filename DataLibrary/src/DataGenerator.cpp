#include "DataGenerator.hpp"
#include <cmath>
#include <stdexcept>

namespace ScientificData
{
double scalarFunction(double x,double y,double amplitude,double frequency)
    {
    return amplitude *
           std::sin(frequency * x) *
           std::cos(frequency * y);
    }

    ScalarFieldData generateData(double xMinimum,double xMaximum,double yMinimum,double yMaximum,std::size_t xSampleCount,std::size_t ySampleCount,double amplitude,double frequency)
    {
        if (xSampleCount < 2)
        {
            throw std::invalid_argument("xSampleCount must be at least 2.");
        }

        if (ySampleCount < 2)
        {
            throw std::invalid_argument("ySampleCount must be at least 2.");
        }
        {
        ScalarFieldData data;

        data.xSampleCount = xSampleCount;
        data.ySampleCount = ySampleCount;

        data.xCoordinates.resize(xSampleCount);
        data.yCoordinates.resize(ySampleCount);
        data.zValues.resize(xSampleCount * ySampleCount);

        const double xSpacing = (xMaximum - xMinimum) / static_cast<double>(xSampleCount - 1);
        const double ySpacing = (yMaximum - yMinimum) / static_cast<double>(ySampleCount - 1);

        for (std::size_t xIndex = 0;
            xIndex < xSampleCount;
            ++xIndex)
        {
    data.xCoordinates[xIndex] = xMinimum + static_cast<double>(xIndex) * xSpacing;
    }

    for (std::size_t yIndex = 0;
        yIndex < ySampleCount;
        ++yIndex)
    {
data.yCoordinates[yIndex] = yMinimum + static_cast<double>(yIndex) * ySpacing;
}

    for (std::size_t yIndex = 0;
        yIndex < ySampleCount;
        ++yIndex)
    {
    for (std::size_t xIndex = 0;
        xIndex < xSampleCount;
        ++xIndex)
        {

            const double x = data.xCoordinates[xIndex];
            const double y = data.yCoordinates[yIndex];
            const std::size_t index = yIndex * xSampleCount + xIndex;

            data.zValues[index] = scalarFunction(x,y,amplitude,frequency);
        }
    }

return data;
}
    }
    }
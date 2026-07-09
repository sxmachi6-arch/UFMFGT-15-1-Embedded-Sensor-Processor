#include "stats.h"
#include <math.h>

double calculateMean(ADCSample *samples, size_t count)
{
    double sum = 0.0;

    for(size_t i = 0; i < count; i++)
    {
        sum += (samples + i)->voltage;
    }

    return sum / count;
}
double calculateMinimum(ADCSample *samples, size_t count)
{
    double minimum = samples[0].voltage;

    for(size_t i = 1; i < count; i++)
    {
        if((samples + i)->voltage < minimum)
        {
            minimum = (samples + i)->voltage;
        }
    }

    return minimum;
}
double calculateMaximum(ADCSample *samples, size_t count)
{
    double maximum = samples[0].voltage;

    for(size_t i = 1; i < count; i++)
    {
        if((samples + i)->voltage > maximum)
        {
            maximum = (samples + i)->voltage;
        }
    }

    return maximum;
}
double calculateStandardDeviation(ADCSample *samples, size_t count)
{
    double mean;
    double sumSquaredDifference = 0.0;

    mean = calculateMean(samples, count);

    for(size_t i = 0; i < count; i++)
    {
        double difference;

        difference = (samples + i)->voltage - mean;

        sumSquaredDifference += difference * difference;
    }

    return sqrt(sumSquaredDifference / count);
}
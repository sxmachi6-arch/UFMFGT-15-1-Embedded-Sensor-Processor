#include "stats.h"

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
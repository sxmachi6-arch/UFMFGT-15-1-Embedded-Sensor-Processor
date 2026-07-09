#include "stats.h"

double calculateMean(ADCSample *samples, size_t count)
{
    double sum = 0.0;

    for(size_t i = 0; i < count; i++)
    {
        sum += samples[i].voltage;
    }

    return sum / count;
}
#include "stats.h"
#include <math.h>

double calculateMean(ADCSample *samples,
                      size_t count,
                      uint8_t channel)
{
    double sum = 0.0;
    size_t sampleCount = 0;

    for(size_t i = 0; i < count; i++)
    {
        if((samples + i)->channel_id == channel)
        {
            sum += (samples + i)->voltage;
            sampleCount++;
        }
    }

    if(sampleCount == 0)
    {
        return 0.0;
    }

    return sum / sampleCount;
}
double calculateMinimum(ADCSample *samples,
                        size_t count,
                        uint8_t channel)
{
    double minimum = 3.3;
    int found = 0;

    for(size_t i = 0; i < count; i++)
    {
        if((samples + i)->channel_id == channel)
        {
            if(!found || (samples + i)->voltage < minimum)
            {
                minimum = (samples + i)->voltage;
                found = 1;
            }
        }
    }

    if(!found)
    {
        return 0.0;
    }

    return minimum;
}
double calculateMaximum(ADCSample *samples,
                        size_t count,
                        uint8_t channel)
{
    double maximum = 0.0;
    int found = 0;

    for(size_t i = 0; i < count; i++)
    {
        if((samples + i)->channel_id == channel)
        {
            if(!found || (samples + i)->voltage > maximum)
            {
                maximum = (samples + i)->voltage;
                found = 1;
            }
        }
    }

    if(!found)
    {
        return 0.0;
    }

    return maximum;
}

double calculateStandardDeviation(ADCSample *samples,
                                  size_t count,
                                  uint8_t channel)
{
    double mean;
    double sumSquaredDifference = 0.0;
    size_t sampleCount = 0;

    mean = calculateMean(samples, count, channel);

    for(size_t i = 0; i < count; i++)
    {
        if((samples + i)->channel_id == channel)
        {
            double difference;

            difference = (samples + i)->voltage - mean;

            sumSquaredDifference += difference * difference;

            sampleCount++;
        }
    }

    if(sampleCount == 0)
    {
        return 0.0;
    }

    return sqrt(sumSquaredDifference / sampleCount);
}


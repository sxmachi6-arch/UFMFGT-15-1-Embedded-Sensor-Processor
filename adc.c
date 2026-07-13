//
// Created by m2-nwosu on 22/06/2026.
//
#include "adc.h"
#include <stdio.h>built


void calculateVoltages(ADCSample *samples, size_t sampleCount)
{
    for(size_t i = 0; i < sampleCount; i++)
    {
        ADCSample *currentSample;

        currentSample = &samples[i];
        uint16_t rawValue;

        rawValue = currentSample->raw_value;
        currentSample->voltage = (rawValue / 4095.0) * 3.3;
    }
}
void detectFaults(ADCSample *samples, size_t sampleCount)
{
    for(size_t i = 0; i < sampleCount; i++)
    {
        ADCSample *currentSample;

        currentSample = &samples[i];
        if(currentSample->voltage > 3.0)
        {
            printf("Overvoltage detected on channel %u at sample %u\n",
                   currentSample->channel_id,
                   currentSample->sequence_number);
        }
        if(currentSample->voltage < 0.3)
        {
            printf("Undervoltage detected on channel %u at sample %u\n",
                   currentSample->channel_id,
                   currentSample->sequence_number);
        }
        if(currentSample->status_flags & 1)
        {
            printf("Sensor fault detected on channel %u at sample %u\n",
                   currentSample->channel_id,
                   currentSample->sequence_number);
        }
    }
}

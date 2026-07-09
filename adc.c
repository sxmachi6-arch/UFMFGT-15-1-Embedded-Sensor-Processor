//
// Created by m2-nwosu on 22/06/2026.
//
#include "adc.h"

void calculateVoltages(ADCSample *samples, size_t sampleCount)
{
    for(size_t i = 0; i < sampleCount; i++)
    {
        ADCSample *currentSample;

        currentSample = &samples[i];
        uint16_t rawValue;

        rawValue = currentSample->raw_value;
        float voltage;

        voltage = (rawValue / 4095.0) * 3.3;
    }
}

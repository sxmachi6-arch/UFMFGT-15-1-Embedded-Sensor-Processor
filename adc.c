//
// Created by m2-nwosu on 22/06/2026.
//
#include "adc.h"
#include <stdio.h>


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
    int overVoltageCount[4] = {0};
    int underVoltageCount[4] = {0};
    int sensorFaultCount[4] = {0};

    for(size_t i = 0; i < sampleCount; i++)
    {
        ADCSample *currentSample;

        currentSample = &samples[i];

        if(currentSample->voltage > 3.0)
        {
            overVoltageCount[currentSample->channel_id]++;

            printf("Overvoltage detected on channel %u at sample %u\n",
                   currentSample->channel_id,
                   currentSample->sequence_number);
        }

        if(currentSample->voltage < 0.3)
        {
            underVoltageCount[currentSample->channel_id]++;

            printf("Undervoltage detected on channel %u at sample %u\n",
                   currentSample->channel_id,
                   currentSample->sequence_number);
        }

        if(currentSample->status_flags & 1)
        {
            sensorFaultCount[currentSample->channel_id]++;

            printf("Sensor fault detected on channel %u at sample %u\n",
                   currentSample->channel_id,
                   currentSample->sequence_number);
        }
    }

    printf("\nFault Summary\n");

    for(int channel = 0; channel < 4; channel++)
    {
        printf("\nChannel %d\n", channel);
        printf("Overvoltage : %d\n", overVoltageCount[channel]);
        printf("Undervoltage: %d\n", underVoltageCount[channel]);
        printf("Sensor Fault: %d\n", sensorFaultCount[channel]);
    }

}
void checkSequenceIntegrity(ADCSample *samples, size_t sampleCount)
{
    for(size_t i = 1; i < sampleCount; i++)
    {
        uint32_t expectedSequence;

        expectedSequence = (samples + i - 1)->sequence_number + 1;

        if((samples + i)->sequence_number != expectedSequence)
        {
            printf("Sequence error detected\n");
            printf("Expected sequence: %u\n", expectedSequence);
            printf("Actual sequence  : %u\n",
                   (samples + i)->sequence_number);
        }
    }
}
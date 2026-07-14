//
// Created by m2-nwosu on 22/06/2026.
//

#ifndef PROGRAMMINGFE_ADC_H
#define PROGRAMMINGFE_ADC_H

#include <stdint.h>

#pragma pack(push,1)

typedef struct
{
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];
} ADCRecord;

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate_hz;
    uint8_t reserved[8];
} FileHeader;

#pragma pack(pop)

typedef struct
{
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    float voltage;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
} ADCSample;
typedef struct
{
    double mean[4];
    double minimum[4];
    double maximum[4];
    double standardDeviation[4];

    int overVoltageCount[4];
    int underVoltageCount[4];
    int sensorFaultCount[4];

    int sequenceErrors;

} AnalysisResults;
void calculateVoltages(ADCSample *samples, size_t sampleCount);
void detectFaults(ADCSample *samples,
                  size_t sampleCount,
                  AnalysisResults *results);
void checkSequenceIntegrity(ADCSample *samples,
                            size_t sampleCount,
                            AnalysisResults *results);

#endif //PROGRAMMINGFE_ADC_H
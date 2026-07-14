#include <stdlib.h>
#include <stdio.h>
#include "adc.h"
#include "io.h"
#include "stats.h"

int main()
{
    FILE *fp;
    FileHeader header;
    ADCSample *samples;
    double mean;
    double minimum;
    double maximum;
    double standardDeviation;
    fp = fopen("adc_sensor_log.bin", "rb");

    if(fp == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    if(readHeader(fp, &header) == 0)
    {
        printf("Failed to read header\n");
        fclose(fp);
        return 1;
    }

    printf("Header successfully read!\n");
    printf("Magic Number   : %u\n", header.magic);
    printf("Version        : %u\n", header.version);
    printf("Channel Count  : %u\n", header.channel_count);
    printf("Record Count   : %u\n", header.record_count);
    printf("Sample Rate    : %u Hz\n", header.sample_rate_hz);
    if(header.magic != 0xADC1BEEF)
{
    printf("Invalid magic number\n");
    fclose(fp);
    return 1;
}
    samples = malloc(header.record_count * sizeof(ADCSample));
    if(samples == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(fp);
        return 1;
    }
    if(readSamples(fp, samples, header.record_count) == 0)
    {
        printf("Failed to read all samples\n");

        free(samples);
        fclose(fp);

        return 1;
    }

    printf("Successfully read %u samples\n", header.record_count);
    printf("\nFirst ADC Sample:\n");
    printf("Timestamp       : %.2f\n", samples[0].timestamp);
    printf("Channel ID      : %u\n", samples[0].channel_id);
    printf("Raw Value       : %u\n", samples[0].raw_value);
    printf("Temperature     : %d\n", samples[0].temperature);
    printf("Status Flags    : %u\n", samples[0].status_flags);
    printf("Sequence Number : %u\n", samples[0].sequence_number);
    printf("\nProcessing all samples...\n");

    calculateVoltages(samples, header.record_count);
    printf("\nVoltage Statistics\n");
    printf("==================\n");

    for(uint8_t channel = 0; channel < 4; channel++)
    {
        mean = calculateMean(samples, header.record_count, channel);

        minimum = calculateMinimum(samples, header.record_count, channel);

        maximum = calculateMaximum(samples, header.record_count, channel);

        standardDeviation = calculateStandardDeviation(samples,
                                                       header.record_count,
                                                       channel);

        printf("\nChannel %u\n", channel);
        printf("Mean Voltage       : %.4f V\n", mean);
        printf("Minimum Voltage    : %.4f V\n", minimum);
        printf("Maximum Voltage    : %.4f V\n", maximum);
        printf("Standard Deviation : %.4f V\n", standardDeviation);
    }
    detectFaults(samples, header.record_count);
    checkSequenceIntegrity(samples, header.record_count);

    if(writeResults("results.txt") == 0)
    {
        printf("Failed to write results file\n");
    }
    free(samples);
    fclose(fp);
    return 0;
}
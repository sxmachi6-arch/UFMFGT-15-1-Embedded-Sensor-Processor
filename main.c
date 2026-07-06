#include <stdlib.h>
#include <stdio.h>
#include "adc.h"
#include "io.h"

int main()
{
    FILE *fp;
    FileHeader header;
    ADCSample *samples;
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
    samples = malloc(header.record_count * sizeof(ADCSample));
    if(samples == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(fp);
        return 1;
    }
    size_t recordsRead;

    recordsRead = fread(samples,
                        sizeof(ADCSample),
                        header.record_count,
                        fp);
if(recordsRead != header.record_count)
{
printf("Failed to read all samples\n");

free(samples);
fclose(fp);

return 1;
}
    printf("Successfully read %zu samples\n", recordsRead);
    printf("\nFirst ADC Sample:\n");
    printf("Timestamp       : %.2f\n", samples[0].timestamp);
    printf("Channel ID      : %u\n", samples[0].channel_id);
    printf("Raw Value       : %u\n", samples[0].raw_value);
    printf("Temperature     : %d\n", samples[0].temperature);
    printf("Status Flags    : %u\n", samples[0].status_flags);
    printf("Sequence Number : %u\n", samples[0].sequence_number);
    printf("\nProcessing all samples...\n");

    for(size_t i = 0; i < header.record_count; i++)
    {

    }

    free(samples);
    fclose(fp);
    return 0;
}
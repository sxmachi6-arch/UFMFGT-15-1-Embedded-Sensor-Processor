#include "io.h"

int readHeader(FILE *fp, FileHeader *header)
{
    size_t result;

    result = fread(header,
                   sizeof(FileHeader),
                   1,
                   fp);

    if(result != 1)
    {
        return 0;
    }

    return 1;
}
int readSamples(FILE *fp,
                ADCSample *samples,
                uint32_t recordCount)
{
    ADCRecord record;

    for(uint32_t i = 0; i < recordCount; i++)
    {
        if(fread(&record, sizeof(ADCRecord), 1, fp) != 1)
        {
            return 0;
        }

        samples[i].timestamp = record.timestamp;
        samples[i].channel_id = record.channel_id;
        samples[i].raw_value = record.raw_value;
        samples[i].temperature = record.temperature;
        samples[i].status_flags = record.status_flags;
        samples[i].sequence_number = record.sequence_number;
    }

    return 1;
}
int writeResults(const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "w");

    if(fp == NULL)
    {
        return 0;
    }

    fprintf(fp, "Embedded Sensor Processor Results\n");
    fprintf(fp, "================================\n\n");

    fprintf(fp, "Analysis completed successfully.\n");

    fclose(fp);

    return 1;
}
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
int writeResults(const char *filename,
                 AnalysisResults *results)
{
    FILE *fp;

    fp = fopen(filename, "w");

    if(fp == NULL)
    {
        return 0;
    }

fprintf(fp, "Embedded Sensor Processor Results\n");
fprintf(fp, "================================\n\n");

fprintf(fp, "Voltage Statistics\n");
fprintf(fp, "------------------\n");

for(int channel = 0; channel < 4; channel++)
{
fprintf(fp, "\nChannel %d\n", channel);
fprintf(fp, "Mean Voltage       : %.4f V\n",
results->mean[channel]);
fprintf(fp, "Minimum Voltage    : %.4f V\n",
results->minimum[channel]);
fprintf(fp, "Maximum Voltage    : %.4f V\n",
results->maximum[channel]);
fprintf(fp, "Standard Deviation : %.4f V\n",
results->standardDeviation[channel]);
}

fprintf(fp, "\nFault Summary\n");
fprintf(fp, "-------------\n");

for(int channel = 0; channel < 4; channel++)
{
fprintf(fp, "\nChannel %d\n", channel);
fprintf(fp, "Overvoltage : %d\n",
results->overVoltageCount[channel]);
fprintf(fp, "Undervoltage: %d\n",
results->underVoltageCount[channel]);
fprintf(fp, "Sensor Fault: %d\n",
results->sensorFaultCount[channel]);
}

fprintf(fp, "\nSequence Errors: %d\n",
results->sequenceErrors);

    fclose(fp);

    return 1;
}
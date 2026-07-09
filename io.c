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
    size_t recordsRead;

    recordsRead = fread(samples,
                        sizeof(ADCSample),
                        recordCount,
                        fp);

    if(recordsRead != recordCount)
    {
        return 0;
    }

    return 1;
}
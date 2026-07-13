#ifndef PROGRAMMINGFE_IO_H
#define PROGRAMMINGFE_IO_H

#include <stdio.h>
#include "adc.h"

int readHeader(FILE *fp,
               FileHeader *header);
int readSamples(FILE *fp,
                ADCSample *samples,
                uint32_t recordCount);
int writeResults(const char *filename);

#endif
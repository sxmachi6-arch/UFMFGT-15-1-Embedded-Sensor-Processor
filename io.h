#ifndef PROGRAMMINGFE_IO_H
#define PROGRAMMINGFE_IO_H

#include <stdio.h>
#include "adc.h"

int readHeader(FILE *fp,
               FileHeader *header);

#endif
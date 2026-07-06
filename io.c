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

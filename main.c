#include <stdio.h>
#include "adc.h"

int main()
{
    printf("ADCSample size = %zu bytes\n",
           sizeof(ADCSample));

    printf("FileHeader size = %zu bytes\n",
           sizeof(FileHeader));

    return 0;
}
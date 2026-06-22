#include <stdio.h>
#include "adc.h"
#include "io.h"

int main()
{
    FILE *fp;

    fp = fopen("adc_sensor_log.bin", "rb");

    if(fp == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    printf("File opened successfully\n");

    fclose(fp);

    return 0;
}
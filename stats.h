#ifndef PROGRAMMINGFE_STATS_H
#define PROGRAMMINGFE_STATS_H

#include "adc.h"

double calculateMean(ADCSample *samples, size_t count);
double calculateMinimum(ADCSample *samples, size_t count);
double calculateMaximum(ADCSample *samples, size_t count);
double calculateStandardDeviation(ADCSample *samples, size_t count);

#endif

#ifndef PROGRAMMINGFE_STATS_H
#define PROGRAMMINGFE_STATS_H

#include "adc.h"

double calculateMean(ADCSample *samples,
                     size_t count,
                     uint8_t channel);

double calculateMinimum(ADCSample *samples,
                        size_t count,
                        uint8_t channel);

double calculateMaximum(ADCSample *samples,
                        size_t count,
                        uint8_t channel);

double calculateStandardDeviation(ADCSample *samples,
                                  size_t count,
                                  uint8_t channel);

#endif

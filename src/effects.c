#include "effects.h"

float effect_fuzz(float sample, void *params)
{
    FuzzParams *p = (FuzzParams *)params;

    float sample_amp = sample * p->gain; // pojacani signal
    if (sample_amp > p->drive_positive)
        return p->drive_positive * sample_amp; // clipping pozitivnog dijela signala
    if (sample_amp < p->drive_negative)
        return p->drive_negative * sample_amp; // clipping negativnog dijela signala
    return sample_amp;                         // clean djelovi
}
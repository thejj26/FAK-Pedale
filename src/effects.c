#include "effects.h"
#include <math.h>

float low_pass(float input, float alpha)    //low pass filter
{
    static float prev_out = 0.0f;
    float output = prev_out + alpha * (input - prev_out);   //sta je alpha blizi 0 to je filter jaci, u pravilu izmedu 0.1 i 1.0
    prev_out = output;
    return output;
}

float effect_fuzz(float sample, void *params, float alpha) // fuzz efekt
{
    FuzzParams *p = (FuzzParams *)params; // dohvaca parametre specificne za fuzz

    float output = sample * p->gain; // prvi stage (preamp)

    if (output > p->drive_positive) //clipping
        output = p->drive_positive;
    if (output < p->drive_negative)
        output = p->drive_negative;

    // low pass je potreban jer be njega ima GROZAN noise i doslovno se nemoze slusat, DC filter je pozeljan jer duh
    // alpha je obicno u rasponu 0.1-0.3, sta vise to je jaci filter
    output = low_pass(output, alpha);

    return output;
}
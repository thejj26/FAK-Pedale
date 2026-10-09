#ifndef EFFECTS_H
#define EFFECTS_H

typedef struct {
    float gain;
    float drive_positive;
    float drive_negative;
} FuzzParams;

float effect_fuzz(float sample, void* params);

#endif
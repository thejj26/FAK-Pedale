#ifndef EFFECTS_H
#define EFFECTS_H

typedef struct {
    float gain;
    float drive_positive;
    float drive_negative;
} FuzzParams;

float low_pass(float input, float alpha);

float effect_fuzz(float sample, void* params, float alpha);

#endif
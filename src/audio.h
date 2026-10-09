#ifndef AUDIO_H
#define AUDIO_H

#include "effects.h"

typedef float (*EffectFunction)(float sample, void *params, float alpha);

int start_audio_engine(const char *, EffectFunction effect, void* params, float alpha);

void stop_audio_engine(void);

#endif
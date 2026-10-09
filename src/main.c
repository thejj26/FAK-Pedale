#include <stdio.h>
#include "audio.h"
#include "effects.h"

int main(void) {
    EffectFunction selected_effect = effect_fuzz;   //odadbrani efekt

    FuzzParams fuzz_params = {  //postavke za fuzz
        .gain = 10.0f,   //gain (no shit)
        .drive_positive = 0.8f, //drive za pozitivni dio
        .drive_negative = -0.5f //drive za negativni dio (sta blize 0 to ce bit vise retro/warm)
    };

    if (start_audio_engine("input.mp3", selected_effect, &fuzz_params, 0.15f) != 0) {  //pcoinje audio engine
        return -1;
    }

    printf("ENTER to stop...\n");
    getchar();

    stop_audio_engine();
    return 0;
}
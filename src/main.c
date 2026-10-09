#include <stdio.h>
#include "audio.h"
#include "effects.h"

int main(void) {
    printf("=== Modular Audio Pedal Running ===\n");
    
    EffectFunction selected_effect = effect_fuzz;

    FuzzParams fuzz_params = {
        .gain = 12.0f,
        .drive_positive = 0.8f,
        .drive_negative = -0.5f
    };

    if (start_audio_engine("input.mp3", selected_effect, &fuzz_params) != 0) {
        return -1;
    }

    printf("Playing with selected effect... Press ENTER to stop.\n");
    getchar();

    stop_audio_engine();
    printf("Audio stopped.\n");
    return 0;
}
// bit cu iskren ovo je chatgpt sve napisa lmao u ovo mi se stvarno nije dalo ulazit al basically ovo se nebi tribalo ni minjat

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "audio.h"
#include <stdio.h>

static ma_decoder g_decoder;
static ma_device g_device;

// Global state holding our generic effect pointer and its context struct
static EffectFunction g_active_effect = NULL;
static void *g_effect_params = NULL;
static float g_active_alpha = 0.15f;

// Audio processing callback triggered by miniaudio
static void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;
    float *out = (float *)pOutput;

    // Read PCM audio frames directly from MP3
    ma_uint64 framesRead;
    ma_decoder_read_pcm_frames(pDecoder, out, frameCount, &framesRead);

    // If end of file is reached, zero out buffer
    if (framesRead == 0)
    {
        for (ma_uint32 i = 0; i < frameCount * pDevice->playback.channels; i++)
        {
            out[i] = 0.0f;
        }
        return;
    }

    ma_uint32 totalSamples = (ma_uint32)framesRead * pDevice->playback.channels;

    // Run the active effect function on every audio sample
    if (g_active_effect != NULL)
    {
        for (ma_uint32 i = 0; i < totalSamples; i++)
        {
            out[i] = g_active_effect(out[i], g_effect_params, g_active_alpha);
        }
    }
}

int start_audio_engine(const char *mp3_filepath, EffectFunction effect, void *params, float alpha)
{
    g_active_effect = effect;
    g_effect_params = params;
    g_active_alpha = alpha;

    // 1. Initialize MP3 decoder
    if (ma_decoder_init_file(mp3_filepath, NULL, &g_decoder) != MA_SUCCESS)
    {
        printf("Error: Could not open MP3 file '%s'\n", mp3_filepath);
        return -1;
    }

    // 2. Configure audio playback device matching MP3 sample rate & channels
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = g_decoder.outputFormat;
    deviceConfig.playback.channels = g_decoder.outputChannels;
    deviceConfig.sampleRate = g_decoder.outputSampleRate;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = &g_decoder;

    // 3. Initialize playback hardware device
    if (ma_device_init(NULL, &deviceConfig, &g_device) != MA_SUCCESS)
    {
        printf("Error: Failed to initialize audio playback device.\n");
        ma_decoder_uninit(&g_decoder);
        return -1;
    }

    // 4. Start audio output stream
    if (ma_device_start(&g_device) != MA_SUCCESS)
    {
        printf("Error: Failed to start audio device.\n");
        ma_device_uninit(&g_device);
        ma_decoder_uninit(&g_decoder);
        return -1;
    }

    return 0;
}

void stop_audio_engine(void)
{
    ma_device_uninit(&g_device);
    ma_decoder_uninit(&g_decoder);
    g_active_effect = NULL;
    g_effect_params = NULL;
    g_active_alpha = 0.15f;
}
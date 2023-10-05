#ifndef __PLUGIN_PARAMETERS_H__
#define __PLUGIN_PARAMETERS_H__

#include <JuceHeader.h>
#include "../BDSP/source/decibel.h"
#include "dsp/SmoothLinear.h"
#include "../BDSP/source/mappings.h"
#include "../BDSP/source/cv/VoltPerOctave.h"
#include "typedefs.h"

// Threshold for volume slider mute
constexpr float OFF_THRESHOLD = -66.0f;

const juce::StringArray CHANNELS_CHOICES{"STEREO", "LEFT", "RIGHT", "SWAPPED"};
enum ChannelsChoice
{
    STEREO = 0,
    LEFT = 1,
    RIGHT = 2,
    SWAPPED = 3
};

// Tune control voltage conversion to 20Hz lowest freq (at -5V)
// With 10 octaves above (+-5V), the highest freq will be 20Hz * 2^10 = 20480Hz (at +5V)
const float ZERO_VOLT_FREQ_BASS_MONO = 20.0f * std::powf(2.0f, 5.0f);

class PluginParameters
{
public:
    explicit PluginParameters(juce::AudioProcessor &processor);

    Apvts apvts;

    ChannelsChoice channels();

    float volume();
    static inline float normalise_volume(float gain);
    static inline float denormalise_volume(float val_norm);
    static inline float denormalise_volume_db(float val_norm);
    float width();
    static inline float denormalise_width(float val_norm);
    bool mono();
    bool bass_mono();
    float bass_mono_freq();
    static inline float normalise_bass_mono_freq(float freq);
    static inline float denormalise_bass_mono_freq(float val_norm);
    float phase_flip_l();
    float phase_flip_r();
    float pan();
    bool dc_block();

    static float denormalise_param_for_ui(float val_norm, const juce::ParameterID &parameter_id);

private:
    static Apvts::ParameterLayout parameter_layout();

    std::atomic<float> *channels_norm;
    std::atomic<float> *volume_norm;
    std::atomic<float> *width_norm;
    std::atomic<float> *mono_norm;
    std::atomic<float> *bass_mono_norm;
    std::atomic<float> *bass_mono_freq_norm;
    std::atomic<float> *phase_flip_l_norm;
    std::atomic<float> *phase_flip_r_norm;
    std::atomic<float> *pan_norm;
    std::atomic<float> *dc_block_norm;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginParameters)
};

#endif // __PLUGIN_PARAMETERS_H__
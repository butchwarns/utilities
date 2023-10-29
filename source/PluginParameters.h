#ifndef PLUGIN_PARAMETERS_H
#define PLUGIN_PARAMETERS_H

#include <JuceHeader.h>
#include "../BDSP/source/decibel.h"
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
    static String channels_string_from_index(int value, int max_string_len);
    float volume();
    static inline float normalise_volume(float gain);
    static inline float denormalise_volume(float val_norm);
    static inline float denormalise_volume_db(float val_norm);
    static String volume_string_from_value(float value, int max_string_len);
    float width();
    static inline float denormalise_width(float val_norm);
    static String width_string_from_value(float value, int max_string_len);
    bool mono();
    static String mono_string_from_bool(bool value, int max_string_len);
    bool bass_mono();
    static String bass_mono_string_from_bool(bool value, int max_string_len);
    float bass_mono_freq();
    static inline float normalise_bass_mono_freq(float freq);
    static inline float denormalise_bass_mono_freq(float val_norm);
    static String bass_mono_freq_string_from_value(float value, int max_string_len);
    float phase_flip_l();
    static String phase_flip_l_string_from_bool(bool value, int max_string_len);
    float phase_flip_r();
    static String phase_flip_r_string_from_bool(bool value, int max_string_len);
    float pan();
    static String pan_string_from_value(float value, int max_string_len);
    bool dc_block();
    static String dc_block_string_from_bool(bool value, int max_string_len);

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

    static void constrain_string_length(String &s, int max_len);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginParameters)
};

#endif // PLUGIN_PARAMETERS_H
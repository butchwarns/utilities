#ifndef PLUGIN_PARAMETERS_H
#define PLUGIN_PARAMETERS_H

#include <JuceHeader.h>
#include "../BDSP/source/decibel.h"
#include "../BDSP/source/mappings.h"
#include "../BDSP/source/cv/VoltPerOctave.h"
#include "typedefs.h"

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
const double ZERO_VOLT_FREQ_BASS_MONO = 20.0 * std::pow(2.0, 5.0);

class PluginParameters
{
public:
    explicit PluginParameters(juce::AudioProcessor &processor);

    Apvts apvts;

    ChannelsChoice channels();
    static String channels_string_from_index(int value, int max_string_len);
    double volume();
    static inline double normalise_volume(double gain);
    static inline double normalise_volume_db(double db);
    static inline double denormalise_volume(double val_norm);
    static inline double denormalise_volume_db(double val_norm);
    static String volume_string_from_value(double value, int max_string_len);
    static std::optional<double> volume_value_from_string(const String &string);
    static inline double skew_volume(double val_norm);
    static inline double unskew_volume(double val_norm);
    double width();
    static inline double normalise_width(double width);
    static inline double normalise_width_percent(double width_percent);
    static inline double denormalise_width(double val_norm);
    static inline double denormalise_width_percent(double val_norm);
    static String width_string_from_value(double value, int max_string_len);
    static std::optional<double> width_value_from_string(const String &string);
    static inline double skew_width(double val_norm);
    static inline double unskew_width(double val_norm);
    bool mono();
    static String mono_string_from_bool(bool value, int max_string_len);
    bool bass_mono();
    static String bass_mono_string_from_bool(bool value, int max_string_len);
    double bass_mono_freq();
    static inline double normalise_bass_mono_freq(double freq);
    static inline double denormalise_bass_mono_freq(double val_norm);
    static String bass_mono_freq_string_from_value(double value, int max_string_len);
    double phase_flip_l();
    double phase_flip_r();
    static inline double denormalise_phase_flip(double val_norm);
    static String phase_flip_l_string_from_bool(bool value, int max_string_len);
    static String phase_flip_r_string_from_bool(bool value, int max_string_len);
    double pan();
    static inline double denormalise_pan(double val_norm);
    static String pan_string_from_value(double value, int max_string_len);
    static std::optional<double> pan_value_from_string(const String &string);
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
#ifndef __PLUGIN_PARAMETERS_H__
#define __PLUGIN_PARAMETERS_H__

#include <JuceHeader.h>
#include "../BDSP/source/decibel.h"
#include "dsp/SmoothLinear.h"
#include "../BDSP/source/maps.h"

typedef juce::AudioProcessorValueTreeState Apvts;

const juce::StringArray CHANNELS_CHOICES{"STEREO", "LEFT", "RIGHT"};
enum ChannelsChoice
{
    STEREO = 0,
    LEFT = 1,
    RIGTH = 2
};

class PluginParameters
{
public:
    PluginParameters(juce::AudioProcessor &processor);
    ~PluginParameters();

    void reset(double _sample_rate);

    juce::ValueTree copy_state();
    juce::Identifier state_type();
    void replace_state(juce::ValueTree const &new_state);

    ChannelsChoice channels();

    float volume();
    static float normalise_volume(float gain);

    float width();

    bool mono();

private:
    Apvts apvts;
    Apvts::ParameterLayout parameter_layout();

    std::atomic<float> *channels_norm;
    std::atomic<float> *volume_norm;
    std::atomic<float> *width_norm;
    std::atomic<float> *mono_norm;

    double sample_rate;
    SmoothLinear smooth_volume;
    SmoothLinear smooth_width;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginParameters)
};

#endif // __PLUGIN_PARAMETERS_H__
#ifndef __PLUGIN_PARAMETERS_H__
#define __PLUGIN_PARAMETERS_H__

#include <JuceHeader.h>
#include "../BDSP/source/decibel.h"
#include "../BDSP/source/maps.h"

typedef juce::AudioProcessorValueTreeState Apvts;

class PluginParameters
{
public:
    PluginParameters(juce::AudioProcessor &processor);
    ~PluginParameters();

    juce::ValueTree copy_state();
    juce::Identifier state_type();
    void replace_state(juce::ValueTree const &new_state);

    float volume();
    static float normalise_volume(float gain);

private:
    Apvts apvts;
    Apvts::ParameterLayout parameter_layout();

    std::atomic<float> *volume_norm;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginParameters)
};

#endif // __PLUGIN_PARAMETERS_H__
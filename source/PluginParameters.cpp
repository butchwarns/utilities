#include "PluginParameters.h"

PluginParameters::PluginParameters(juce::AudioProcessor &processor)
    : apvts(processor, nullptr, "parameters", parameter_layout())
{
    volume_norm = apvts.getRawParameterValue("volume");
}

PluginParameters::~PluginParameters()
{
}

juce::ValueTree PluginParameters::copy_state()
{
    return apvts.copyState();
}

juce::Identifier PluginParameters::state_type()
{
    return apvts.state.getType();
}

void PluginParameters::replace_state(juce::ValueTree const &new_state)
{
    apvts.replaceState(new_state);
}

float PluginParameters::volume()
{
    const float db = bdsp::maps::map_linear_norm_pos<float>(*volume_norm, -66.1f, 35.0f);
    const float gain = bdsp::decibel::db_to_raw_gain_off(db, -66.0f);
    return gain;
}

float PluginParameters::normalise_volume(float gain)
{
    // Find dB value for given gain
    float db = 0.0f;
    if (gain <= bdsp::decibel::db_to_raw_gain(-66.0f))
    {
        db = -66.0f;
    }
    else
    {
        db = bdsp::decibel::raw_gain_to_db(gain);
    }

    // Normalise
    const float norm = bdsp::maps::map_linear<float>(db, -66.0, 35.0f, 0.0f, 1.0f);

    return norm;
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    std::unique_ptr<ParameterGroup> utility_grp = std::make_unique<ParameterGroup>("utility", "UTILITY", "|");
    utility_grp->addChild(std::make_unique<juce::AudioParameterFloat>("volume", "VOLUME", 0.0f, 1.0f, normalise_volume(1.0f)));

    layout.add(std::move(utility_grp));

    return layout;
}
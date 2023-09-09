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
    return *volume_norm;
}

Apvts::ParameterLayout PluginParameters::parameter_layout()
{
    Apvts::ParameterLayout layout;

    typedef juce::AudioProcessorParameterGroup ParameterGroup;

    std::unique_ptr<ParameterGroup> utility_grp = std::make_unique<ParameterGroup>("utility", "UTILITY", "|");
    utility_grp->addChild(std::make_unique<juce::AudioParameterFloat>("volume", "VOLUME", 0.0f, 1.0f, 0.0f));

    layout.add(std::move(utility_grp));

    return layout;
}
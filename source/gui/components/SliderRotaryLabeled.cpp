#include "SliderRotaryLabeled.h"

SliderRotaryLabeled::SliderRotaryLabeled(PluginParameters &p, ParameterID param_id)
    : slider(p, param_id)
{
    addAndMakeVisible(&label);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(Label::textColourId, Colours::black);

    addAndMakeVisible(&slider);
}

void SliderRotaryLabeled::paint(Graphics &g)
{
}

void SliderRotaryLabeled::resized()
{
    auto bounds = getLocalBounds();
    label.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider.setBounds(bounds);
}
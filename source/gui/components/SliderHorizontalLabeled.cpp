#include "SliderHorizontalLabeled.h"

SliderHorizontalLabeled::SliderHorizontalLabeled(PluginParameters &p, ParameterID param_id)
    : slider(p, param_id)
{
    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);

    addAndMakeVisible(&slider);
}

void SliderHorizontalLabeled::paint(Graphics &g)
{
    ignoreUnused(g);
}

void SliderHorizontalLabeled::resized()
{
    auto bounds = getLocalBounds();
    label.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider.setBounds(bounds);
}
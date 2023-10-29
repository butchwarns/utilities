#include "SliderRotaryLabeled.h"

SliderRotaryLabeled::SliderRotaryLabeled(PluginParameters &p, String param_id, std::function<String(float value, int maximumStringLength)> string_from_value)
    : slider(p, param_id, string_from_value)
{
    addAndMakeVisible(&label);
    addAndMakeVisible(&slider);
}

void SliderRotaryLabeled::paint(Graphics &g)
{
    ignoreUnused(g);
}

void SliderRotaryLabeled::resized()
{
    auto bounds = getLocalBounds();
    label.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider.setBounds(bounds);
}
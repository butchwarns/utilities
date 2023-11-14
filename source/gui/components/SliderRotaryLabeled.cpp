#include "SliderRotaryLabeled.h"

SliderRotaryLabeled::SliderRotaryLabeled(PluginParameters &p,
                                         String param_id,
                                         std::function<String(float value, int maximumStringLength)> string_from_value,
                                         std::function<std::optional<double>(const String &string)> value_from_string)
    : slider(p, param_id, string_from_value, value_from_string)
{
    addAndMakeVisible(&label);
    addAndMakeVisible(&slider);
}

void SliderRotaryLabeled::setTooltip(String msg)
{
    slider.slider.setTooltip(msg);
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
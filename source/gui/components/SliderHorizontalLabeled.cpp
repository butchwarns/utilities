#include "SliderHorizontalLabeled.h"

SliderHorizontalLabeled::SliderHorizontalLabeled(PluginParameters &p,
                                                 String param_id,
                                                 std::function<String(float value, int maximumStringLength)> string_from_value,
                                                 std::function<std::optional<double>(String string)> value_from_string)
    : slider(p, param_id, string_from_value, value_from_string)
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
#include "SliderHorizontal.h"

SliderHorizontal::SliderHorizontal(PluginParameters &_p, String param_id, std::function<String(float value, int maximumStringLength)> _string_from_value)
    : p(_p), string_from_value(_string_from_value)
{
    slider.addListener(this);

    addAndMakeVisible(&slider);
    slider.setSliderStyle(Slider::LinearBar);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setRange(0.0f, 1.0f, 0.0001f);
    slider.setSkewFactor(1.0f); // Don't skew!

    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    label.setInterceptsMouseClicks(false, false); // Mouse should react to slider, label is overlayed

    attachment = std::make_unique<SliderAttachment>(p.apvts, param_id, slider);

    touch();
}

void SliderHorizontal::touch()
{
    sliderValueChanged(&slider);
}

void SliderHorizontal::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void SliderHorizontal::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(bounds);
    label.setBounds(bounds);
}

void SliderHorizontal::sliderValueChanged(Slider *s)
{
    const auto val_norm = (float)(s->getValue());
    const String val_formatted = string_from_value(val_norm, 9);

    label.setText(val_formatted, dontSendNotification);
}

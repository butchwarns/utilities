#include "SliderRotary.h"

SliderRotary::SliderRotary(PluginParameters &_p, String param_id, std::function<String(float value, int maximumStringLength)> _string_from_value)
    : p(_p), string_from_value(_string_from_value)
{
    slider.addListener(this);

    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);

    addAndMakeVisible(&slider);
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setColour(Slider::textBoxTextColourId, Colours::black);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setRange(0.0f, 1.0f, 0.0f);

    attachment = std::make_unique<SliderAttachment>(p.apvts, param_id, slider);

    touch();
}

void SliderRotary::touch()
{
    sliderValueChanged(&slider);
}

void SliderRotary::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void SliderRotary::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(bounds.removeFromTop(KNOB_DIM));
    label.setBounds(bounds);
}

void SliderRotary::sliderValueChanged(Slider *slider)
{
    const double val_norm = slider->getValue();

    const String val_formatted = string_from_value((float)val_norm, 9);

    label.setText(val_formatted, dontSendNotification);
}
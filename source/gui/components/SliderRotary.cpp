#include "SliderRotary.h"

SliderRotary::SliderRotary(PluginParameters &_p, String param_id, std::function<String(float value, int maximumStringLength)> _string_from_value)
    : p(_p), string_from_value(_string_from_value), shadower(shadow)
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

    shadow.colour = Colours::black.withAlpha(0.32f);
}

void SliderRotary::touch()
{
    sliderValueChanged(&slider);
}

void SliderRotary::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds().removeFromTop(50);
    bounds.reduce((COLUMN2_WIDTH - KNOB_DIM) / 2, 0);
    bounds.reduce(PAD, PAD);

    Path knob_path;
    knob_path.addEllipse(bounds.toFloat().reduced(OUTLINE));

    shadow.offset = Point<int>(5, 5);
    shadow.radius = 12;
    shadow.drawForPath(g, knob_path);
}

void SliderRotary::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(bounds.removeFromTop(KNOB_DIM));
    label.setBounds(bounds);
}

void SliderRotary::sliderValueChanged(Slider *s)
{
    const double val_norm = s->getValue();

    const String val_formatted = string_from_value((float)val_norm, 9);

    label.setText(val_formatted, dontSendNotification);
}
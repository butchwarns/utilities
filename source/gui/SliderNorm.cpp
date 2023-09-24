#include "SliderNorm.h"

SliderNorm::SliderNorm(PluginParameters &_p, ParameterID _param_id) : p(_p), param_id(_param_id), num_decimal_places(2), value_suffix("")
{
    slider.addListener(this);

    addAndMakeVisible(&slider);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setRange(0.0f, 1.0f);
    slider.setSkewFactor(1.0f); // Don't skew!

    addAndMakeVisible(&label);
}

void SliderNorm::set_decimal_places_to_display(int _num_decimal_places)
{
    num_decimal_places = _num_decimal_places;
}

void SliderNorm::set_value_suffix(juce::String _value_suffix)
{
    value_suffix = juce::String(" ") + _value_suffix;
}

void SliderNorm::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void SliderNorm::resized()
{
    auto bounds = getLocalBounds();
    slider.setBounds(bounds.removeFromTop(SLIDER_DIM));
    label.setBounds(bounds);
}

void SliderNorm::sliderValueChanged(Slider *slider)
{
    const float val_denorm = p.denormalise_param(slider->getValue(), param_id);
    auto val = juce::String::toDecimalStringWithSignificantFigures(val_denorm, num_decimal_places);
    label.setText(val + value_suffix, dontSendNotification);
}
#include "SliderHorizontal.h"

SliderHorizontal::SliderHorizontal(PluginParameters &_p, ParameterID _param_id) : p(_p), param_id(_param_id), num_decimal_places(2), value_suffix("")
{
    slider.addListener(this);

    addAndMakeVisible(&slider);
    slider.setSliderStyle(Slider::LinearBar);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setRange(0.0f, 1.0f, 0.001f);
    slider.setSkewFactor(1.0f); // Don't skew!

    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    label.setInterceptsMouseClicks(false, false); // Mouse should react to slider, label is overlayed
}

void SliderHorizontal::set_decimal_places_to_display(int _num_decimal_places)
{
    num_decimal_places = _num_decimal_places;
}

void SliderHorizontal::set_value_suffix(juce::String _value_suffix)
{
    value_suffix = _value_suffix;
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

void SliderHorizontal::sliderValueChanged(Slider *slider)
{
    const float val_denorm = p.denormalise_param_for_ui((float)(slider->getValue()), param_id);

    // Format value string to the correct number of decimal places
    std::stringstream val_formatted;
    val_formatted << std::fixed << std::setprecision(num_decimal_places);
    val_formatted << val_denorm << value_suffix.toStdString();

    label.setText(val_formatted.str(), dontSendNotification);
}
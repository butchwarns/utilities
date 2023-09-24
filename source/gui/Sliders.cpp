#include "Sliders.h"

Sliders::Sliders(PluginParameters &p) : slider_norm_volume(p, "volume"), slider_norm_width(p, "width")
{
    addAndMakeVisible(&volume);
    volume.setText("VOLUME", dontSendNotification);
    volume.setJustificationType(juce::Justification::centred);
    volume.setColour(Label::textColourId, Colours::black);
    volume.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&slider_norm_volume);
    slider_norm_volume.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_norm_volume.slider.setColour(Slider::textBoxTextColourId, Colours::black);
    slider_norm_volume.set_decimal_places_to_display(1);
    slider_norm_volume.set_value_suffix("dB");

    addAndMakeVisible(&width);
    width.setText("WIDTH", dontSendNotification);
    width.setJustificationType(juce::Justification::centred);
    width.setColour(Label::textColourId, Colours::black);
    width.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&slider_norm_width);
    slider_norm_width.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_norm_width.slider.setColour(Slider::textBoxTextColourId, Colours::black);
    slider_norm_width.set_decimal_places_to_display(1);
    slider_norm_width.set_value_suffix("%");

    attachment_volume.reset(new SliderAttachment(p.get_apvts(), "volume", slider_norm_volume.slider));
    attachment_width.reset(new SliderAttachment(p.get_apvts(), "width", slider_norm_width.slider));
}

void Sliders::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Sliders::resized()
{
    auto bounds = getLocalBounds();

    auto volume_bounds = bounds.removeFromLeft(bounds.getWidth() / 2.0f);
    volume.setBounds(volume_bounds.removeFromTop(LABEL_HEIGHT));
    slider_norm_volume.setBounds(volume_bounds);

    width.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider_norm_width.setBounds(bounds);
}
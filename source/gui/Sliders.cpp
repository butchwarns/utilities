#include "Sliders.h"

Sliders::Sliders(PluginParameters &p) : slider_volume(p, "volume"), slider_width(p, "width")
{

    addAndMakeVisible(&slider_volume);
    slider_volume.label.setText("VOLUME", dontSendNotification);
    slider_volume.label.setJustificationType(juce::Justification::centred);
    slider_volume.label.setColour(Label::textColourId, Colours::black);
    slider_volume.label.getProperties().set("gui_class", "bold");
    slider_volume.slider.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_volume.slider.setColour(Slider::textBoxTextColourId, Colours::black);
    slider_volume.slider.slider.getProperties().set("gui_class", "slider_rotary_off");
    slider_volume.slider.set_decimal_places_to_display(1);
    slider_volume.slider.set_value_suffix("dB");

    addAndMakeVisible(&slider_width);
    slider_width.label.setText("WIDTH", dontSendNotification);
    slider_width.label.getProperties().set("gui_class", "bold");
    slider_width.slider.slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_width.slider.setColour(Slider::textBoxTextColourId, Colours::black);
    slider_width.slider.set_decimal_places_to_display(0);
    slider_width.slider.set_value_suffix("%");

    attachment_volume.reset(new SliderAttachment(p.get_apvts(), "volume", slider_volume.slider.slider));
    attachment_width.reset(new SliderAttachment(p.get_apvts(), "width", slider_width.slider.slider));
}

void Sliders::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Sliders::resized()
{
    auto bounds = getLocalBounds();

    auto volume_bounds = bounds.removeFromLeft(bounds.getWidth() / 2.0f);

    slider_volume.setBounds(volume_bounds);
    slider_width.setBounds(bounds);
}
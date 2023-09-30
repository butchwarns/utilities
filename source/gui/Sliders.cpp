#include "Sliders.h"

Sliders::Sliders(PluginParameters &p) : slider_width(p, "width"), slider_volume(p, "volume"), slider_pan(p, "pan")
{
    addAndMakeVisible(&slider_width);
    slider_width.label.setText("WIDTH", dontSendNotification);
    slider_width.label.setJustificationType(juce::Justification::centred);
    slider_width.label.setColour(Label::textColourId, Colours::black);
    slider_width.label.getProperties().set("gui_class", "bold");
    slider_width.slider.set_decimal_places_to_display(0);
    slider_width.slider.set_value_suffix("%");

    addAndMakeVisible(&slider_volume);
    slider_volume.label.setText("VOLUME", dontSendNotification);
    slider_volume.label.setJustificationType(juce::Justification::centred);
    slider_volume.label.setColour(Label::textColourId, Colours::black);
    slider_volume.label.getProperties().set("gui_class", "bold");
    slider_volume.slider.slider.getProperties().set("gui_class", "slider_rotary_off");
    slider_volume.slider.set_decimal_places_to_display(1);
    slider_volume.slider.set_value_suffix("dB");

    addAndMakeVisible(&slider_pan);
    slider_pan.label.setText("PAN", dontSendNotification);
    slider_pan.label.setJustificationType(juce::Justification::centred);
    slider_pan.label.setColour(Label::textColourId, Colours::black);
    slider_pan.label.getProperties().set("gui_class", "bold");
    slider_pan.slider.slider.getProperties().set("param", "pan");
    slider_pan.slider.slider.getProperties().set("gui_class", "slider_symmetric");

    attachment_width = std::make_unique<SliderAttachment>(p.get_apvts(), "width", slider_width.slider.slider);
    attachment_pan = std::make_unique<SliderAttachment>(p.get_apvts(), "pan", slider_pan.slider.slider);
    attachment_volume = std::make_unique<SliderAttachment>(p.get_apvts(), "volume", slider_volume.slider.slider);
}

void Sliders::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Sliders::resized()
{
    auto bounds = getLocalBounds();

    slider_width.setBounds(bounds.removeFromTop(SLIDER_ROTARY_LABELED_HEIGHT));
    slider_pan.setBounds(bounds.removeFromBottom(SLIDER_ROTARY_LABELED_HEIGHT));
    // bounds.reduce(0, bounds.getHeight() - (SLIDER_ROTARY_LABELED_HEIGHT / 2));
    slider_volume.setBounds(bounds);
}
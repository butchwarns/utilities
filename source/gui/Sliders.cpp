#include "Sliders.h"

Sliders::Sliders()
{
    addAndMakeVisible(&volume);
    volume.setText("VOLUME", dontSendNotification);
    volume.setJustificationType(juce::Justification::centred);
    volume.setColour(Label::textColourId, Colours::black);
    volume.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&slider_volume);
    slider_volume.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_volume.setTextBoxStyle(juce::Slider::TextBoxBelow, true, SLIDER_WIDTH, LABEL_HEIGHT);
    slider_volume.setColour(Slider::textBoxTextColourId, Colours::black);
    slider_volume.setNumDecimalPlacesToDisplay(1);
    slider_volume.setTextValueSuffix("dB");

    addAndMakeVisible(&width);
    width.setText("WIDTH", dontSendNotification);
    width.setJustificationType(juce::Justification::centred);
    width.setColour(Label::textColourId, Colours::black);
    width.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&slider_width);
    slider_width.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_width.setTextBoxStyle(juce::Slider::TextBoxBelow, true, SLIDER_WIDTH, LABEL_HEIGHT);
    slider_width.setColour(Slider::textBoxTextColourId, Colours::black);
    slider_width.setNumDecimalPlacesToDisplay(0);
    slider_width.setTextValueSuffix("%");
}

void Sliders::paint(juce::Graphics &g)
{
}

void Sliders::resized()
{
    auto bounds = getLocalBounds();

    auto volume_bounds = bounds.removeFromLeft(bounds.getWidth() / 2.0f);
    volume.setBounds(volume_bounds.removeFromTop(LABEL_HEIGHT));
    slider_volume.setBounds(volume_bounds);

    width.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider_width.setBounds(bounds);
}
#include "Sliders.h"

Sliders::Sliders()
{
    addAndMakeVisible(&volume);
    volume.setText("VOLUME", dontSendNotification);
    volume.setJustificationType(juce::Justification::centred);
    volume.setFont(FONT_SIZE);

    addAndMakeVisible(&slider_volume);
    slider_volume.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_volume.setTextBoxStyle(juce::Slider::TextBoxBelow, true, SLIDER_WIDTH, LABEL_HEIGHT);

    addAndMakeVisible(&width);
    width.setText("WIDTH", dontSendNotification);
    width.setJustificationType(juce::Justification::centred);
    width.setFont(FONT_SIZE);

    addAndMakeVisible(&slider_width);
    slider_width.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider_width.setTextBoxStyle(juce::Slider::TextBoxBelow, true, SLIDER_WIDTH, LABEL_HEIGHT);
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
#include "BassMono.h"

BassMono::BassMono()
{
    addAndMakeVisible(&bass_mono);
    bass_mono.setText("BASS MONO", dontSendNotification);
    bass_mono.setJustificationType(juce::Justification::centred);
    bass_mono.setFont(FONT_SIZE);

    addAndMakeVisible(&active);
    active.setText("ACTIVE", dontSendNotification);
    active.setJustificationType(juce::Justification::centred);
    active.setFont(FONT_SIZE);

    addAndMakeVisible(&checkbox);

    addAndMakeVisible(&frequency);
    frequency.setText("FREQUENCY", dontSendNotification);
    frequency.setJustificationType(juce::Justification::centred);
    frequency.setFont(FONT_SIZE);

    addAndMakeVisible(&slider);
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
}

void BassMono::paint(juce::Graphics &g)
{
}

void BassMono::resized()
{
    auto bounds = getLocalBounds();

    bass_mono.setBounds(bounds.removeFromTop(LABEL_HEIGHT));

    bounds.removeFromTop(PAD);

    auto active_check_bounds = bounds.removeFromTop(LABEL_HEIGHT);
    checkbox.setBounds(active_check_bounds.removeFromRight(CHECKBOX_DIM));
    active.setBounds(active_check_bounds);

    bounds.removeFromTop(PAD);

    frequency.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider.setBounds(bounds);
}

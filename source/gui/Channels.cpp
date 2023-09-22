#include "Channels.h"
#include "../PluginParameters.h"

Channels::Channels()
{
    addAndMakeVisible(&channels);
    channels.setText("CHANNELS", dontSendNotification);
    channels.setJustificationType(juce::Justification::centred);
    channels.setFont(FONT_SIZE);

    addAndMakeVisible(&selector);
    selector.addItemList(CHANNELS_CHOICES, 0);

    addAndMakeVisible(&mono);
    mono.setText("MONO", dontSendNotification);
    mono.setJustificationType(juce::Justification::centred);
    mono.setFont(FONT_SIZE);

    addAndMakeVisible(&checkbox);
}

void Channels::paint(juce::Graphics &g)
{
}

void Channels::resized()
{
    auto bounds = getLocalBounds();

    channels.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(5);
    selector.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(5);
    checkbox.setBounds(bounds.removeFromRight(CHECKBOX_DIM));
    mono.setBounds(bounds);
}

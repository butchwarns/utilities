#include "Footer.h"

Footer::Footer()
{
    addAndMakeVisible(&version);
    version.setText("v0.1.0", dontSendNotification);
    version.setJustificationType(juce::Justification::centred);
    version.setColour(juce::Label::textColourId, juce::Colours::white);
    version.getProperties().set("gui_class", "label");

    addAndMakeVisible(&bw);
    bw.setText("->BW", dontSendNotification);
    bw.setJustificationType(juce::Justification::centred);
    bw.setColour(juce::Label::textColourId, juce::Colours::white);

    addAndMakeVisible(&link);
    link.setURL(juce::URL("https://butchwarns.de/"));
}

void Footer::paint(juce::Graphics &g)
{
    g.fillAll(BLACK);
}

void Footer::resized()
{
    auto bounds = getLocalBounds();

    bounds.removeFromLeft(PAD);
    bounds.removeFromRight(PAD);

    version.setBounds(bounds.removeFromLeft((int)((float)(bounds.getWidth()) / 2.0f)));
    bw.setBounds(bounds);
    link.setBounds(bounds);
}
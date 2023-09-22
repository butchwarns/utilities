#include "Footer.h"

Footer::Footer()
{
    addAndMakeVisible(&version);
    version.setText("v0.1.0", dontSendNotification);
    version.setJustificationType(juce::Justification::left);
    version.setFont(FONT_SIZE);

    addAndMakeVisible(&bw);
    bw.setText("BW", dontSendNotification);
    bw.setFont(FONT_SIZE);
    bw.setJustificationType(juce::Justification::right);

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

    version.setBounds(bounds.removeFromLeft(bounds.getWidth() / 2.0f));
    bw.setBounds(bounds);
    link.setBounds(bounds);
}
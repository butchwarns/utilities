#include "Header.h"

Header::Header()
{
    addAndMakeVisible(&title);

    title.setText("UTILITY", dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setColour(juce::Label::textColourId, juce::Colours::white);
    title.setFont(FONT_SIZE_TITLE);
}

void Header::paint(juce::Graphics &g)
{
    g.fillAll(BLACK);
}

void Header::resized()
{
    title.setBounds(getLocalBounds());
}
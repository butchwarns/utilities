#include "Spacer.h"

void Spacer::paint(juce::Graphics &g)
{
    g.setColour(Colours::black);
    g.fillRect(getLocalBounds());
}

void Spacer::resized()
{
}
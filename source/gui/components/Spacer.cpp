#include "Spacer.h"

void Spacer::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();
    bounds.reduce(0, 5);

    g.setColour(Colours::black);
    g.fillRect(bounds);
}

void Spacer::resized()
{
}
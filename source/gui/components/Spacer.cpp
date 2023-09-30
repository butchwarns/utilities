#include "Spacer.h"

void Spacer::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();

    if (bounds.getWidth() > bounds.getHeight())
    {
        // Horizontal spacer
        bounds.reduce(0, 5);
    }
    else
    {
        // Vertical spacer
        bounds.reduce(5, 0);
    }

    g.setColour(Colours::black);
    g.fillRect(bounds);
}

void Spacer::resized()
{
}
#include "Spacer.h"

void Spacer::paint(juce::Graphics &g)
{
    g.drawRect(0, PAD, getLocalBounds().getWidth(), SPACER_LINE, 1);
}

void Spacer::resized()
{
}
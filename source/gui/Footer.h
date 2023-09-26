#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "colours.h"

class Footer : public juce::Component
{
public:
    Footer();

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label version;
    juce::Label bw;
    juce::HyperlinkButton link;
};
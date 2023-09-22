#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "colours.h"

class Header : public juce::Component
{
public:
    Header();
    ~Header() = default;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label title;
};
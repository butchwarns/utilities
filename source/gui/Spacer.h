#pragma once

#include <JuceHeader.h>
#include "sizes.h"

class Spacer : public juce::Component
{
public:
    Spacer();
    ~Spacer() = default;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;
};
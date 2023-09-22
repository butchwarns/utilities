#pragma once

#include <JuceHeader.h>
#include "sizes.h"

class Channels : public juce::Component
{
public:
    Channels();
    ~Channels() = default;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label channels;
    juce::ComboBox selector;
    juce::Label mono;
    juce::ToggleButton checkbox;
};
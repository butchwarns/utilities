#pragma once

#include <JuceHeader.h>
#include "sizes.h"

class BassMono : public juce::Component
{
public:
    BassMono();
    ~BassMono() = default;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label bass_mono;
    juce::Label active;
    juce::ToggleButton checkbox;
    juce::Label frequency;
    juce::Slider slider;
};
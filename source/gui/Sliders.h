#pragma once

#include <JuceHeader.h>
#include "sizes.h"

class Sliders : public juce::Component
{
public:
    Sliders();
    ~Sliders() = default;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label volume;
    juce::Slider slider_volume;
    juce::Label width;
    juce::Slider slider_width;
};
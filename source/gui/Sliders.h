#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"

class Sliders : public juce::Component
{
public:
    Sliders(Apvts &apvts);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label volume;
    juce::Slider slider_volume;
    juce::Label width;
    juce::Slider slider_width;

    std::unique_ptr<SliderAttachment> attachment_volume;
    std::unique_ptr<SliderAttachment> attachment_width;
};
#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"

class BassMono : public juce::Component
{
public:
    BassMono(Apvts &apvts);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label bass_mono;
    juce::Label active;
    juce::ToggleButton checkbox;
    juce::Label frequency;
    juce::Slider slider;

    std::unique_ptr<ButtonAttachment> attachment_checkbox;
    std::unique_ptr<SliderAttachment> attachment_slider;
};
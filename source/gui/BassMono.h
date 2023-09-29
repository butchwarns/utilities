#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"
#include "../PluginParameters.h"
#include "components/SliderHorizontalLabeled.h"

class BassMono : public juce::Component
{
public:
    BassMono(PluginParameters &p);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label bass_mono;
    juce::Label active;
    juce::ToggleButton checkbox;
    SliderHorizontalLabeled slider;

    std::unique_ptr<ButtonAttachment> attachment_checkbox;
    std::unique_ptr<SliderAttachment> attachment_slider;
};
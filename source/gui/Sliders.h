#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"
#include "SliderRotary.h"
#include "../PluginParameters.h"

class Sliders : public juce::Component
{
public:
    Sliders(PluginParameters &p);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label volume;
    SliderRotary slider_norm_volume;
    juce::Label width;
    SliderRotary slider_norm_width;

    std::unique_ptr<SliderAttachment> attachment_volume;
    std::unique_ptr<SliderAttachment> attachment_width;
};
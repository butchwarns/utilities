#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"
#include "components/SliderRotaryLabeled.h"
#include "../PluginParameters.h"

class Sliders : public juce::Component
{
public:
    Sliders(PluginParameters &p);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    SliderRotaryLabeled slider_width;
    SliderRotaryLabeled slider_volume;
    SliderRotaryLabeled slider_pan;
};
#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"
#include "../PluginParameters.h"
#include "components/SliderHorizontalLabeled.h"
#include "components/CheckboxLabeled.h"

class BassMono : public juce::Component
{
public:
    BassMono(PluginParameters &p);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label bass_mono;
    CheckboxLabeled checkbox;
    SliderHorizontalLabeled slider;

    std::unique_ptr<ButtonAttachment> attachment_checkbox;
    std::unique_ptr<SliderAttachment> attachment_slider;
};
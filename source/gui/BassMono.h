#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"
#include "../PluginParameters.h"
#include "components/SliderHorizontalLabeled.h"
#include "components/CheckboxLabeled.h"
#include "components/LabelTitle.h"

class BassMono : public juce::Component
{
public:
    BassMono(PluginParameters &p);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    LabelTitle bass_mono;
    CheckboxLabeled checkbox;
    SliderHorizontalLabeled slider;
};
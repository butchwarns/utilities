#pragma once

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderRotary : public juce::Component, public juce::Slider::Listener
{
public:
    SliderRotary(PluginParameters &p, String param_id, std::function<String(float value, int maximumStringLength)> _string_from_value);

    juce::Slider slider;
    juce::Label label;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    void sliderValueChanged(Slider *slider) override;

protected:
    PluginParameters &p;

    std::function<String(float value, int maximumStringLength)> string_from_value;

    std::unique_ptr<SliderAttachment> attachment;
};
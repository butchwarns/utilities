#pragma once

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderHorizontal : public juce::Component, public juce::Slider::Listener
{
public:
    SliderHorizontal(PluginParameters &_p, ParameterID _param_id, std::function<String(float value, int maximumStringLength)> _string_from_value);

    juce::Slider slider;
    juce::Label label;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    PluginParameters &p;
    juce::ParameterID param_id;

    std::unique_ptr<SliderAttachment> attachment;

    std::function<String(float value, int maximumStringLength)> string_from_value;

    void sliderValueChanged(Slider *slider) override;
};
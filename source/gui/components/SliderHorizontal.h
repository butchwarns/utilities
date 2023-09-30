#pragma once

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderHorizontal : public juce::Component, public juce::Slider::Listener
{
public:
    SliderHorizontal(PluginParameters &_p, ParameterID _param_id = ParameterID(""));

    juce::Slider slider;
    juce::Label label;

    void set_decimal_places_to_display(int _num_decimal_places);
    void set_value_suffix(juce::String suffix);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    PluginParameters &p;
    juce::ParameterID param_id;

    int num_decimal_places;
    juce::String value_suffix;

    std::unique_ptr<SliderAttachment> attachment;

    void sliderValueChanged(Slider *slider) override;
};
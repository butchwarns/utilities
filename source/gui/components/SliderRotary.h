#pragma once

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderRotary : public juce::Component, public juce::Slider::Listener
{
public:
    SliderRotary(PluginParameters &p, ParameterID param_id);

    juce::Slider slider;
    juce::Label label;

    void set_decimal_places_to_display(int _num_decimal_places);
    void set_value_suffix(juce::String suffix);

    void touch();

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    void sliderValueChanged(Slider *slider) override;

protected:
    PluginParameters &p;
    juce::ParameterID param_id;

    int num_decimal_places;
    juce::String value_suffix;

    std::unique_ptr<SliderAttachment> attachment;
};
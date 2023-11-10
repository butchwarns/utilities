#pragma once

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderRotary : public Component, public Slider::Listener, public Label::Listener
{
public:
    SliderRotary(PluginParameters &p,
                 String param_id,
                 std::function<String(float value, int maximumStringLength)> _string_from_value,
                 std::function<std::optional<double>(const String &string)> _value_from_string);

    juce::Slider slider;
    juce::Label label;

    void touch();

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    void sliderValueChanged(Slider *s) override;
    void labelTextChanged(Label *labelThatHasChanged) override;

    void set_value(double val);

    PluginParameters &p;

    std::function<String(float value, int maximumStringLength)> string_from_value;
    std::function<std::optional<double>(String string)> value_from_string;

    std::unique_ptr<SliderAttachment> attachment;

    DropShadow shadow;
    DropShadower shadower;
};
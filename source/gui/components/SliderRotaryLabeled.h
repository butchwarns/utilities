#pragma once

#include <JuceHeader.h>
#include "SliderRotary.h"
#include "../sizes.h"
#include "../../PluginParameters.h"
#include "LabelTitle.h"

class SliderRotaryLabeled : public Component
{
public:
    SliderRotaryLabeled(PluginParameters &p,
                        String param_id,
                        std::function<String(float value, int maximumStringLength)> string_from_value,
                        std::function<std::optional<double>(const String &string)> value_from_string);

    LabelTitle label;
    SliderRotary slider;

private:
    void paint(Graphics &g) override;
    void resized() override;
};
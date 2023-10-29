#pragma once

#include <JuceHeader.h>
#include "SliderRotary.h"
#include "../sizes.h"
#include "../../PluginParameters.h"
#include "LabelTitle.h"

class SliderRotaryLabeled : public Component
{
public:
    SliderRotaryLabeled(PluginParameters &p, String param_id, std::function<String(float value, int maximumStringLength)> string_from_value);

    LabelTitle label;
    SliderRotary slider;

private:
    void paint(Graphics &g) override;
    void resized() override;
};
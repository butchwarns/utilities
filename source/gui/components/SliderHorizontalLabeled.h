#pragma once

#include <JuceHeader.h>
#include "SliderHorizontal.h"
#include "../sizes.h"
#include "../../PluginParameters.h"

class SliderHorizontalLabeled : public Component
{
public:
    SliderHorizontalLabeled(PluginParameters &p, ParameterID param_id, std::function< String(float value, int maximumStringLength)> string_from_value);

    Label label;
    SliderHorizontal slider;

private:
    void paint(Graphics &g) override;
    void resized() override;
};
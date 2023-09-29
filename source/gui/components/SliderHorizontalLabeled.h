#pragma once

#include <JuceHeader.h>
#include "SliderHorizontal.h"
#include "../sizes.h"
#include "../../PluginParameters.h"

class SliderHorizontalLabeled : public Component
{
public:
    SliderHorizontalLabeled(PluginParameters &p, ParameterID param_id);

    Label label;
    SliderHorizontal slider;

private:
    void paint(Graphics &g) override;
    void resized() override;
};
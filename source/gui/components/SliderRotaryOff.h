#pragma once

#include "SliderRotary.h"

class SliderRotaryOff : public SliderRotary
{
public:
    SliderRotaryOff(PluginParameters &_p, ParameterID _param_id = ParameterID(""));

private:
    virtual void sliderValueChanged(Slider *slider) override;
};
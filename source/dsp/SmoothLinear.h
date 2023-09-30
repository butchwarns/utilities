#pragma once

#include <JuceHeader.h>

class SmoothLinear
{
public:
    SmoothLinear();
    ~SmoothLinear() = default;

    void reset(double _sample_rate);
    void set_time_constant(float time_constant);

    void set_target_val(float _target_val);
    float next();

private:
    double sample_rate;
    float num_frames;
    float target_val;
    float state;
    float delta;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SmoothLinear)
};
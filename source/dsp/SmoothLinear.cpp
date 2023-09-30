#include "SmoothLinear.h"

SmoothLinear::SmoothLinear()
    : sample_rate(1.0), num_frames(1.0f), target_val(0.0f), state(0.0f), delta(0.0f)
{
}

void SmoothLinear::reset(double _sample_rate)
{
    state = 0.0;
    sample_rate = _sample_rate;
}

void SmoothLinear::set_time_constant(float time_constant)
{
    num_frames = time_constant * (float)sample_rate;
}

void SmoothLinear::set_target_val(float _target_val)
{
    target_val = _target_val;
    delta = (target_val - state) / num_frames;
}

float SmoothLinear::next()
{
    // Rising
    if (delta >= 0.0f)
    {
        if (state >= target_val)
        {
            delta = 0.0f;
        }
    }
    // Falling
    else
    {
        if (state <= target_val)
        {
            delta = 0.0f;
        }
    }

    state += delta;
    return state;
}
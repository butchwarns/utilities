#pragma once

#include <JuceHeader.h>
#include "colours.h"

class Look : public juce::LookAndFeel_V4
{
public:
    Look() = default;
    ~Look() = default;

private:
    void drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle slider_style, Slider &slider) override;

    void drawTickBox(Graphics &g, Component &component,
                     float x, float y, float w, float h,
                     const bool ticked,
                     const bool isEnabled,
                     const bool shouldDrawButtonAsHighlighted,
                     const bool shouldDrawButtonAsDown) override;

    virtual void drawLabel(Graphics &g, Label &label) override;
};

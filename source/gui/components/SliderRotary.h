/*
SliderRotary.h
Copyright (C) 2023 Butch Warns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SLIDER_ROTARY_H
#define SLIDER_ROTARY_H

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderRotary
    : public Component,
      public Slider::Listener,
      public Label::Listener
{
public:
    SliderRotary(PluginParameters &p,
                 const String &param_id,
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

#endif // SLIDER_ROTARY_H
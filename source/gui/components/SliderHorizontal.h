/*
SliderHorizontal.h
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

#pragma once

#include <JuceHeader.h>
#include "../sizes.h"
#include "../../PluginParameters.h"
#include <sstream>
#include <iomanip>

class SliderHorizontal : public juce::Component,
                         public juce::Slider::Listener,
                         public ::Label::Listener
{
public:
    SliderHorizontal(PluginParameters &_p,
                     String param_id,
                     std::function<String(float value, int maximumStringLength)> _string_from_value,
                     std::function<std::optional<double>(String string)> _value_from_string);

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

    std::unique_ptr<SliderAttachment> attachment;

    std::function<String(float value, int maximumStringLength)> string_from_value;
    std::function<std::optional<double>(String string)> value_from_string;
};
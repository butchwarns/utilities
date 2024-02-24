/*
SliderHorizontal.cpp
Copyright (C) 2024 Butch Warns

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

#include "SliderHorizontal.h"
#include "../colours.h"

SliderHorizontal::SliderHorizontal(PluginParameters &_p,
                                   const String &param_id,
                                   std::function<String(float value, int maximumStringLength)> _string_from_value,
                                   std::function<std::optional<double>(String string)> _value_from_string)
    : p(_p),
      attachment(nullptr),
      string_from_value(_string_from_value),
      value_from_string(_value_from_string)
{
    slider.addListener(this);

    addAndMakeVisible(&slider);
    slider.setSliderStyle(Slider::LinearBar);
    slider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    slider.setRange(0.0f, 1.0f, 0.0001f);

    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setEditable(true);
    label.addListener(this);
    label.setColour(TextEditor::highlightColourId, RED_TRANSPARENT);

    attachment = std::make_unique<SliderAttachment>(p.apvts, param_id, slider);

    touch();
}

void SliderHorizontal::touch()
{
    sliderValueChanged(&slider);
}

void SliderHorizontal::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void SliderHorizontal::resized()
{
    auto bounds = getLocalBounds();

    slider.setBounds(bounds.removeFromTop(SLIDER_HORIZONTAL_NO_LABEL_HEIGHT));
    label.setBounds(bounds);
}

void SliderHorizontal::sliderValueChanged(Slider *s)
{
    const double val_norm = s->getValue();

    const String val_formatted = string_from_value((float)val_norm, 9);

    label.setText(val_formatted, dontSendNotification);
}

void SliderHorizontal::labelTextChanged(Label *labelThatHasChanged)
{
    const String text = labelThatHasChanged->getText();
    const std::optional<double> opt = value_from_string(text);

    if (opt.has_value())
    {
        set_value(opt.value());
    }
    else
    {
        touch();
    }
}

void SliderHorizontal::set_value(double val)
{
    const double val_old = slider.getValue();

    slider.setValue(val, sendNotification);

    // If value did not change, trigger update manually
    if (slider.getValue() - val_old < 0.0001)
    {
        sliderValueChanged(&slider);
    }
}
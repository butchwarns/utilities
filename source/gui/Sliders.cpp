/*
Sliders.cpp
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

#include "Sliders.h"

Sliders::Sliders(PluginParameters &p)
    : slider_width(p, "width", p.width_string_from_value, p.width_value_from_string),
      slider_volume(p, "volume", p.volume_string_from_value, p.volume_value_from_string),
      slider_pan(p, "pan", p.pan_string_from_value, p.pan_value_from_string)
{
    addAndMakeVisible(&slider_width);
    slider_width.label.set_text("WIDTH");
    slider_width.label.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&slider_volume);
    slider_volume.label.set_text("VOLUME");
    slider_volume.label.getProperties().set("gui_class", "bold");
    slider_volume.slider.slider.getProperties().set("gui_class", "slider_rotary_off");

    addAndMakeVisible(&slider_pan);
    slider_pan.label.set_text("PAN");
    slider_pan.label.getProperties().set("gui_class", "bold");
    slider_pan.slider.slider.getProperties().set("param", "pan");
    slider_pan.slider.slider.getProperties().set("gui_class", "slider_symmetric");
}

void Sliders::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Sliders::resized()
{
    auto bounds = getLocalBounds();

    slider_width.setBounds(bounds.removeFromTop(SLIDER_ROTARY_LABELED_HEIGHT));
    slider_pan.setBounds(bounds.removeFromBottom(SLIDER_ROTARY_LABELED_HEIGHT));
    bounds.reduce(0, (bounds.getHeight() - SLIDER_ROTARY_LABELED_HEIGHT) / 2);
    slider_volume.setBounds(bounds);
}
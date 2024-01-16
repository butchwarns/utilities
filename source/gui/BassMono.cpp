/*
BassMono.cpp
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

#include "BassMono.h"

BassMono::BassMono(PluginParameters &p)
    : check_on(p, "bass_mono"),
      check_cue(p, "bass_mono_cue"),
      slider(p, "bass_mono_freq", p.bass_mono_freq_string_from_value, p.bass_mono_freq_value_from_string)
{
    addAndMakeVisible(&bass_mono);
    bass_mono.set_text("BASS MONO");
    bass_mono.getProperties().set("text_style", "bold");

    addAndMakeVisible(&check_on);
    check_on.label.setText("ON", dontSendNotification);

    addAndMakeVisible(&check_cue);
    check_cue.label.setText("CUE", dontSendNotification);

    addAndMakeVisible(&slider);
    slider.label.setText("FREQUENCY", dontSendNotification);
}

void BassMono::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void BassMono::resized()
{
    auto bounds = getLocalBounds();

    bass_mono.setBounds(bounds.removeFromTop(LABEL_HEIGHT));

    bounds.removeFromTop(PAD);

    auto check_bounds = bounds.removeFromTop(CHECKBOX_LABELED_HEIGHT);
    check_on.setBounds(check_bounds.removeFromLeft(check_bounds.getWidth() / 2));
    check_cue.setBounds(check_bounds);

    bounds.removeFromTop(2 * PAD);

    slider.setBounds(bounds);
}

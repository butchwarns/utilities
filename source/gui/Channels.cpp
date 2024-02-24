/*
Channels.cpp
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

#include "Channels.h"

Channels::Channels(PluginParameters &p) : checkbox(p, "mono")
{
    addAndMakeVisible(&channels);
    channels.set_text("CHANNELS");

    addAndMakeVisible(&selector);
    selector.addItemList(CHANNELS_CHOICES, 1);
    selector.setColour(ComboBox::textColourId, Colours::black);
    selector.setJustificationType(Justification::centred);

    addAndMakeVisible(&checkbox);
    checkbox.label.setText("MONO", dontSendNotification);

    attachment_selector = std::make_unique<ComboBoxAttachment>(p.apvts, "channels", selector);
    attachment_checkbox = std::make_unique<ButtonAttachment>(p.apvts, "mono", checkbox.checkbox);
}

void Channels::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Channels::resized()
{
    auto bounds = getLocalBounds();

    channels.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(PAD);
    selector.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(2 * PAD);
    checkbox.setBounds(bounds);
}

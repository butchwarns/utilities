/*
Footer.cpp
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

#include "Footer.h"

Footer::Footer()
{
    // Parse current version number
    auto version_json = String::fromUTF8(BinaryData::version_json, BinaryData::version_jsonSize);
    auto version_var = JSON::parse(version_json);
    const auto &v = version_var["version"];

    addAndMakeVisible(&version);
    version.setText(v, dontSendNotification);
    version.setJustificationType(juce::Justification::centred);
    version.setColour(juce::Label::textColourId, juce::Colours::white);
    version.getProperties().set("gui_class", "label");

    addAndMakeVisible(&bw);
    bw.setText("->BW", dontSendNotification);
    bw.setJustificationType(juce::Justification::centred);
    bw.setColour(juce::Label::textColourId, juce::Colours::white);

    addAndMakeVisible(&link);
    link.setURL(juce::URL("https://butchwarns.de/"));
}

void Footer::paint(juce::Graphics &g)
{
    g.fillAll(BLACK);
}

void Footer::resized()
{
    auto bounds = getLocalBounds();

    bounds.removeFromLeft(PAD);
    bounds.removeFromRight(PAD);

    version.setBounds(bounds.removeFromLeft((int)((float)(bounds.getWidth()) / 2.0f)));
    bw.setBounds(bounds);
    link.setBounds(bounds);
}
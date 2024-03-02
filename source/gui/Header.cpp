/*
Header.cpp
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

#include "Header.h"

Header::Header()
{
    addAndMakeVisible(&title);
    title.setText("UTILITIES", dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    title.setColour(juce::Label::textColourId, juce::Colours::white);
    title.getProperties().set("gui_class", "title");
}

void Header::paint(juce::Graphics &g)
{
    g.fillAll(BLACK);
}

void Header::resized()
{
    title.setBounds(getLocalBounds());
}
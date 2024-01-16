/*
CheckboxLabeled.cpp
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

#include "CheckboxLabeled.h"

CheckboxLabeled::CheckboxLabeled(PluginParameters &p, const String &param_id) : attachment(nullptr)
{
    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    label.getProperties().set("text_style", "italic");

    addAndMakeVisible(&checkbox);

    attachment = std::make_unique<ButtonAttachment>(p.apvts, param_id, checkbox);
}

void CheckboxLabeled::paint(Graphics &g)
{
    ignoreUnused(g);
}

void CheckboxLabeled::resized()
{
    auto bounds = getLocalBounds();

    checkbox.setBounds(bounds.removeFromRight(CHECKBOX_DIM));
    label.setBounds(bounds);
}
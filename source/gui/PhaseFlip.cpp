/*
PhaseFlip.cpp
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

#include "PhaseFlip.h"

PhaseFlip::PhaseFlip(PluginParameters &p) : check_l(p, "phase_flip_l"), check_r(p, "phase_flip_r")
{
    addAndMakeVisible(&label);
    label.setText("PHASE FLIP", dontSendNotification);
    label.setColour(Label::textColourId, Colours::black);
    label.setJustificationType(Justification::centred);
    label.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&check_l);
    check_l.label.setText("L", dontSendNotification);

    addAndMakeVisible(&check_r);
    check_r.label.setText("R", dontSendNotification);

    attachment_check_l = std::make_unique<ButtonAttachment>(p.apvts, "phase_flip_l", check_l.checkbox);
    attachment_check_r = std::make_unique<ButtonAttachment>(p.apvts, "phase_flip_r", check_r.checkbox);
}

void PhaseFlip::paint(Graphics &g)
{
    ignoreUnused(g);
}

void PhaseFlip::resized()
{
    auto bounds = getLocalBounds();

    label.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(PAD);

    check_l.setBounds(bounds.removeFromLeft((bounds.getWidth() - PAD) / 2));
    bounds.removeFromLeft(PAD);
    check_r.setBounds(bounds);
}
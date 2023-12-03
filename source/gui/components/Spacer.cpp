/*
Spacer.cpp
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

#include "Spacer.h"

void Spacer::paint(juce::Graphics &g)
{
    auto bounds = getLocalBounds();

    if (bounds.getWidth() > bounds.getHeight())
    {
        // Horizontal spacer
        bounds.reduce(0, 5);
    }
    else
    {
        // Vertical spacer
        bounds.reduce(5, 0);
    }

    g.setColour(Colours::black);
    g.fillRect(bounds);
}

void Spacer::resized()
{
}
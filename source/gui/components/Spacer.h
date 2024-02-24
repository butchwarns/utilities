/*
Spacer.h
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

#ifndef SPACER_H
#define SPACER_H

#include <JuceHeader.h>
#include "../sizes.h"

class Spacer : public juce::Component
{
public:
    Spacer() = default;

private:
    void paint(juce::Graphics &g) override;
    void resized() override;
};

#endif // SPACER_H

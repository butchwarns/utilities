/*
CheckboxLabeled.h
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

#ifndef CHECKBOX_LABELED_H
#define CHECKBOX_LABELED_H

#include <JuceHeader.h>
#include "../../PluginParameters.h"
#include "../sizes.h"

class CheckboxLabeled : public Component
{
public:
    CheckboxLabeled(PluginParameters &p, const String &param_id);

    juce::Label label;
    juce::ToggleButton checkbox;

private:
    void paint(Graphics &g) override;
    void resized() override;

    std::unique_ptr<ButtonAttachment> attachment;
};

#endif // CHECKBOX_LABELED_H
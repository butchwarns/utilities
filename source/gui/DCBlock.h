/*
DCBlock.h
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

#ifndef DC_BLOCK_H
#define DC_BLOCK_H

#include <JuceHeader.h>
#include "../PluginParameters.h"
#include "components/CheckboxLabeled.h"
#include "components/LabelTitle.h"
#include "../typedefs.h"

class DCBlock : public Component
{
public:
    DCBlock(PluginParameters &p);

private:
    void paint(Graphics &g) override;
    void resized() override;

    LabelTitle label;
    CheckboxLabeled checkbox;

    std::unique_ptr<ButtonAttachment> attachment;
};

#endif // DC_BLOCK_H
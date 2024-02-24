/*
WindowContents.h
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

#ifndef WINDOW_CONTENTS_H
#define WINDOW_CONTENTS_H

#include <JuceHeader.h>
#include "../PluginParameters.h"
#include "Header.h"
#include "Footer.h"
#include "Channels.h"
#include "BassMono.h"
#include "Sliders.h"
#include "PhaseFlip.h"
#include "DCBlock.h"
#include "components/Spacer.h"

class WindowContents : public Component
{
public:
    WindowContents(PluginParameters &params);

private:
    void paint(Graphics &g) override;
    void resized() override;

    Header header;
    Footer footer;

    Spacer spacer_vertical;

    Sliders sliders;
    Spacer spacer1;
    Channels channels;
    Spacer spacer2;
    BassMono bass_mono;
    Spacer spacer3;
    PhaseFlip phase_flip;
    DCBlock dc_block;
};

#endif // WINDOW_CONTENTS_H
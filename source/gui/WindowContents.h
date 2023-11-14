#pragma once

#include <JuceHeader.h>
#include "../PluginParameters.h"
#include "Header.h"
#include "Footer.h"
#include "Channels.h"
#include "BassMono.h"
#include "Sliders.h"
#include "PhaseFlip.h"
#include "DCBlock.h"
#include "Tooltip.h"
#include "components/Spacer.h"

class WindowContents : public Component
{
public:
    WindowContents(PluginParameters &params);

    void set_tooltip(String msg);

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
    Tooltip tooltip;
};
#pragma once

#include <JuceHeader.h>
#include "../PluginParameters.h"
#include "components/CheckboxLabeled.h"
#include "../typedefs.h"

class PhaseFlip : public Component
{
public:
    PhaseFlip(PluginParameters &p);

private:
    void paint(Graphics &g) override;
    void resized() override;

    Label label;
    CheckboxLabeled check_l;
    CheckboxLabeled check_r;

    std::unique_ptr<ButtonAttachment> attachment_check_l;
    std::unique_ptr<ButtonAttachment> attachment_check_r;
};
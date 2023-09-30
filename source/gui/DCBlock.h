#pragma once

#include <JuceHeader.h>
#include "../PluginParameters.h"
#include "components/CheckboxLabeled.h"
#include "../typedefs.h"

class DCBlock : public Component
{
public:
    DCBlock(PluginParameters &p);

private:
    void paint(Graphics &g) override;
    void resized() override;

    Label label;
    CheckboxLabeled checkbox;

    std::unique_ptr<ButtonAttachment> attachment;
};
#pragma once

#include <JuceHeader.h>
#include "../../PluginParameters.h"
#include "../sizes.h"

class CheckboxLabeled : public Component
{
public:
    CheckboxLabeled(PluginParameters &p, ParameterID param_id);

    juce::Label label;
    juce::ToggleButton checkbox;

private:
    void paint(Graphics &g) override;
    void resized() override;

    std::unique_ptr<ButtonAttachment> attachment;
};
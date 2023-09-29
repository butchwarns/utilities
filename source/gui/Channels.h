#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"
#include "../PluginParameters.h"
#include "components/CheckboxLabeled.h"

class Channels : public juce::Component
{
public:
    Channels(PluginParameters &p);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label channels;
    juce::ComboBox selector;
    CheckboxLabeled checkbox;

    std::unique_ptr<ComboBoxAttachment> attachment_selector;
    std::unique_ptr<ButtonAttachment> attachment_checkbox;
};
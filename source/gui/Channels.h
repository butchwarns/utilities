#pragma once

#include <JuceHeader.h>
#include "sizes.h"
#include "../typedefs.h"

class Channels : public juce::Component
{
public:
    Channels(Apvts &apvts);

private:
    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Label channels;
    juce::ComboBox selector;
    juce::Label mono;
    juce::ToggleButton checkbox;

    std::unique_ptr<ComboBoxAttachment> attachment_selector;
    std::unique_ptr<ButtonAttachment> attachment_checkbox;
};
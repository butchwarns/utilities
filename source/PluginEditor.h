#pragma once

#include "PluginProcessor.h"
#include "gui/colours.h"
#include "gui/Look.h"
#include "typedefs.h"
#include "PluginParameters.h"
#include "gui/WindowContents.h"

class PluginEditor : public AudioProcessorEditor, public ComponentBoundsConstrainer
{
public:
    explicit PluginEditor(PluginProcessor &, PluginParameters &params);
    ~PluginEditor() override;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    PluginProcessor &processor_ref;

    Look look;

    WindowContents window_contents;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
#pragma once

#include "PluginProcessor.h"
#include "gui/Header.h"
#include "gui/Footer.h"
#include "gui/Channels.h"
#include "gui/BassMono.h"
#include "gui/Sliders.h"
#include "gui/Spacer.h"
#include "gui/colours.h"
#include "gui/Look.h"
#include "typedefs.h"

class PluginEditor : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(PluginProcessor &, Apvts &apvts);
    ~PluginEditor() override = default;

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    PluginProcessor &processorRef;

    Look look;

    Header header;
    Footer footer;

    Sliders sliders;
    Spacer spacer1;
    Channels channels;
    Spacer spacer2;
    BassMono bass_mono;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
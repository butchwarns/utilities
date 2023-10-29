#include "BassMono.h"

BassMono::BassMono(PluginParameters &p)
    : checkbox(p, "bass_mono"), slider(p, "bass_mono_freq", p.bass_mono_freq_string_from_value)
{
    addAndMakeVisible(&bass_mono);
    bass_mono.set_text("BASS MONO");
    bass_mono.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&checkbox);
    checkbox.label.setText("ACTIVE", dontSendNotification);

    addAndMakeVisible(&slider);
    slider.label.setText("FREQUENCY", dontSendNotification);
}

void BassMono::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void BassMono::resized()
{
    auto bounds = getLocalBounds();

    bass_mono.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(PAD);

    auto active_check_bounds = bounds.removeFromTop(LABEL_HEIGHT);
    checkbox.setBounds(active_check_bounds.removeFromTop(CHECKBOX_DIM));

    slider.setBounds(bounds);
}

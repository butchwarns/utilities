#include "BassMono.h"

BassMono::BassMono(PluginParameters &p) : slider(p, "bass_mono_freq")
{
    addAndMakeVisible(&bass_mono);
    bass_mono.setText("BASS MONO", dontSendNotification);
    bass_mono.setJustificationType(Justification::centred);
    bass_mono.setColour(Label::textColourId, Colours::black);
    bass_mono.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&active);
    active.setText("ACTIVE", dontSendNotification);
    active.setJustificationType(Justification::centred);
    active.setColour(Label::textColourId, Colours::black);
    active.getProperties().set("gui_class", "italic");

    addAndMakeVisible(&checkbox);

    addAndMakeVisible(&frequency);
    frequency.setText("FREQUENCY", dontSendNotification);
    frequency.setJustificationType(Justification::centred);
    frequency.setColour(Label::textColourId, Colours::black);

    addAndMakeVisible(&slider);
    slider.set_decimal_places_to_display(0);
    slider.set_value_suffix("Hz");

    attachment_slider = std::make_unique<SliderAttachment>(p.get_apvts(), "bass_mono_freq", slider.slider);
    attachment_checkbox = std::make_unique<ButtonAttachment>(p.get_apvts(), "bass_mono", checkbox);
}

void BassMono::paint(juce::Graphics &g)
{
}

void BassMono::resized()
{
    auto bounds = getLocalBounds();

    bass_mono.setBounds(bounds.removeFromTop(LABEL_HEIGHT));

    bounds.removeFromTop(PAD);

    auto active_check_bounds = bounds.removeFromTop(LABEL_HEIGHT);
    checkbox.setBounds(active_check_bounds.removeFromRight(CHECKBOX_DIM));
    active.setBounds(active_check_bounds);

    bounds.removeFromTop(PAD);

    frequency.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    slider.setBounds(bounds);
}
#include "BassMono.h"

BassMono::BassMono(PluginParameters &p) : checkbox(p, "bass_mono_active"), slider(p, "bass_mono_freq")
{
    addAndMakeVisible(&bass_mono);
    bass_mono.setText("BASS MONO", dontSendNotification);
    bass_mono.setJustificationType(Justification::centred);
    bass_mono.setColour(Label::textColourId, Colours::black);
    bass_mono.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&checkbox);
    checkbox.label.setText("ACTIVE", dontSendNotification);

    addAndMakeVisible(&slider);
    slider.label.setText("FREQUENCY", dontSendNotification);
    slider.slider.set_decimal_places_to_display(0);
    slider.slider.set_value_suffix("Hz");

    attachment_slider = std::make_unique<SliderAttachment>(p.get_apvts(), "bass_mono_freq", slider.slider.slider);
    attachment_checkbox = std::make_unique<ButtonAttachment>(p.get_apvts(), "bass_mono", checkbox.checkbox);
}

void BassMono::paint(juce::Graphics &g)
{
}

void BassMono::resized()
{
    auto bounds = getLocalBounds();

    bass_mono.setBounds(bounds.removeFromTop(LABEL_HEIGHT));

    auto active_check_bounds = bounds.removeFromTop(LABEL_HEIGHT);
    checkbox.setBounds(active_check_bounds.removeFromTop(CHECKBOX_DIM));

    slider.setBounds(bounds);
}

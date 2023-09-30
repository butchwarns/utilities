#include "Channels.h"

Channels::Channels(PluginParameters &p) : checkbox(p, "mono")
{
    addAndMakeVisible(&channels);
    channels.setText("CHANNELS", dontSendNotification);
    channels.setJustificationType(juce::Justification::centred);
    channels.setColour(Label::textColourId, Colours::black);
    channels.getProperties().set("gui_class", "bold");

    addAndMakeVisible(&selector);
    selector.addItemList(CHANNELS_CHOICES, 1);
    selector.setColour(ComboBox::textColourId, Colours::black);
    selector.setJustificationType(Justification::centred);

    addAndMakeVisible(&checkbox);
    checkbox.label.setText("MONO", dontSendNotification);

    attachment_selector = std::make_unique<ComboBoxAttachment>(p.get_apvts(), "channels", selector);
    attachment_checkbox = std::make_unique<ButtonAttachment>(p.get_apvts(), "mono", checkbox.checkbox);
}

void Channels::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Channels::resized()
{
    auto bounds = getLocalBounds();

    channels.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    selector.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(PAD);
    checkbox.setBounds(bounds);
}

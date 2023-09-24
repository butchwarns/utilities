#include "Channels.h"
#include "../PluginParameters.h"

Channels::Channels(Apvts &apvts)
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

    addAndMakeVisible(&mono);
    mono.setText("MONO", dontSendNotification);
    mono.setJustificationType(juce::Justification::centred);
    mono.setColour(Label::textColourId, Colours::black);
    mono.getProperties().set("gui_class", "italic");

    addAndMakeVisible(&checkbox);

    attachment_selector = std::make_unique<ComboBoxAttachment>(apvts, "channels", selector);
    attachment_checkbox = std::make_unique<ButtonAttachment>(apvts, "mono", checkbox);
}

void Channels::paint(juce::Graphics &g)
{
    ignoreUnused(g);
}

void Channels::resized()
{
    auto bounds = getLocalBounds();

    channels.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(5);
    selector.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(5);
    checkbox.setBounds(bounds.removeFromRight(CHECKBOX_DIM));
    mono.setBounds(bounds);
}

#include "DCBlock.h"

DCBlock::DCBlock(PluginParameters &p) : checkbox(p, "dc_block")
{
    addAndMakeVisible(&label);
    label.setText("DC BLOCK", dontSendNotification);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    label.getProperties().set("gui_class", "bold");
    checkbox.label.setText("CUT", dontSendNotification);

    addAndMakeVisible(&checkbox);

    attachment = std::make_unique<ButtonAttachment>(p.get_apvts(), "dc_block", checkbox.checkbox);
}

void DCBlock::paint(Graphics &g)
{
    ignoreUnused(g);
}

void DCBlock::resized()
{
    auto bounds = getLocalBounds();

    label.setBounds(bounds.removeFromTop(LABEL_HEIGHT));
    bounds.removeFromTop(PAD);
    checkbox.setBounds(bounds);
}
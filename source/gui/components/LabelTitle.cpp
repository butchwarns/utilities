#include "LabelTitle.h"

LabelTitle::LabelTitle()
{
    addAndMakeVisible(&label);
    label.setJustificationType(Justification::centred);
    label.setColour(Label::textColourId, Colours::black);
    label.getProperties().set("gui_class", "bold");
}

void LabelTitle::set_text(String text)
{
    label.setText(text, dontSendNotification);
}

void LabelTitle::paint(Graphics &g)
{
    ignoreUnused(g);
}

void LabelTitle::resized()
{
    label.setBounds(getLocalBounds());
}